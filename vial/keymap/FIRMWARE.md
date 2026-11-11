# Lily58 Pro · firmware Vial

## Antes de instalar

Con el firmware anterior conectado, guardá el diseño actual en un archivo nuevo desde **File → Save current layout** en Vial. Conservá ese archivo junto al HEX anterior. Un `.vil` guarda la configuración que entiende Vial, no una imagen cruda de toda la EEPROM. La referencia incorporada aquí es `../layout/lily58.vil`, versión 1, UID `0x0648397D5BFCFD7E`, protocolos Vial 6 y VIA 9. Si cambiaste algo en el teclado después de exportarlo, ese cambio solo estará en el respaldo nuevo.

**La primera instalación puede restaurar los valores de fábrica.** Este fork normalmente usa una firma aleatoria por compilación para validar los datos VIA/Vial. Para este formato se fijó la firma `A2F2EF` de la última compilación local anterior. Si el teclado tiene esa firma y la misma estructura, conserva sus cambios. Si tiene otra firma o EEPROM inválida, Vial inicializa sus datos con los valores compilados. La versión que efectivamente está instalada en el teclado se desconoce. Tras actualizar, podés abrir el respaldo nuevo en Vial para recuperar tus ediciones.

## Compilar e instalar

El checkout local es `/Users/manuel/vial-qmk`, fork `vial-kb/vial-qmk`, revisión `dd43959ae5c08d8a28d38a1acf7b04e86b14a344`. Su directorio `keyboards/lily58/rev1/keymaps/vial` enlaza a esta carpeta Git. Las extensiones de reset en `rules.mk` se apoyan en las reglas de esa revisión.

```sh
cd /Users/manuel/vial-qmk
make lily58/rev1:vial
```

Al pasar la comprobación de tamaño, el build archiva en `vial/firmware` del repositorio una copia `lily58_rev1_vial-YYYY-MM-DD_HH-MM-SS.hex` con hora local.

1. Con USB desconectado, separá las mitades. Conectá por USB solo la primera.
2. Abrí el HEX fechado en QMK Toolbox, seleccioná ATmega32U4 y dejá Auto-Flash desactivado. Pulsá reset en esa mitad (doble pulsación si tu placa lo requiere). Cuando Toolbox detecte Caterina/AVR109, pulsá **Flash** y esperá a que termine.
3. Desconectá USB y repetí con el mismo HEX en la otra mitad. Con ambas sin alimentación, conectá el TRRS y por último el USB a la izquierda. El firmware conserva serial en D2 y la configuración de maestro izquierdo. Con USB en la derecha este montaje puede interpretar las mitades al revés.

## Qué envía cada perfil

La tecla principal del pulgar izquierdo es GUI en el archivo exportado (fila 4, columna 4). Se eligió esa posición para el atajo principal en ambos sistemas.

| Perfil en OLED | Selección automática | Pulgar + C | Tecla física Ctrl izquierda |
|---|---|---|---|
| MAC | macOS, iOS e iPadOS identificado como iOS | Cmd+C | Ctrl |
| NO MAC | Windows, Linux y cualquier equipo identificado por QMK como Linux | Ctrl+C | GUI |
| DEFAULT | Arranque, OS_UNSURE o valor desconocido | GUI+C, tal como está exportado | Ctrl |

La detección usa la heurística USB oficial en la mitad maestra. Android y ChromeOS dependen del resultado que entregue esa heurística. En un dock o KVM que mantenga el teclado alimentado, si el perfil queda desactualizado, reconectá el USB o elegí el modo manual.

En NON-MAC el firmware intercambia Ctrl y GUI a izquierda y derecha mediante los dos bits de `keymap_config` en RAM. QMK aplica este mecanismo a teclas físicas y a modificadores compuestos, incluidos los Mod-Tap. Layer-Tap sigue el camino normal de QMK. Alt/Option conserva su posición. Las macros exportadas se reproducen con sus modificadores literales: M1/M2 siguen enviando GUI+Shift+3/4, incluso en NON-MAC. Son los atajos de captura del mapa original.

### Selección manual desde Vial

En **Keymap**, elegí una celda libre y asignale una tecla de la pestaña **User**. En el mapa exportado, las posiciones físicas 1, 2, 3 y 4 de la fila numérica en la capa 3 están en `KC_NO` y pueden usarse para los cuatro controles. Si usás tu propio layout, comprobá primero qué hay en esas posiciones. Para acceder a la capa 3 con los valores de fábrica, mantené los dos Tap Dance de capa. La asignación de cada tecla se guarda normalmente desde Vial.

| Tecla en Vial | Efecto al pulsarla |
|---|---|
| AUTO | Retoma el último resultado de QMK |
| FORCE_MAC | Fuerza MAC |
| FORCE_NON_MAC | Fuerza NON-MAC |
| FORCE_DEFAULT | Fuerza DEFAULT |

El cambio entra en vigor al soltar las teclas y modificadores activos. El modo manual dura la sesión y el próximo arranque comienza en AUTO. Se preservan las asignaciones originales de las cuatro capas.

## Valores de fábrica y recuperación

El reset de mapa de este fork copia 4 × 10 × 6 keycodes de flash y restablece las tablas dinámicas. La extensión carga los Tap Dance y overrides exportados y refresca la caché de Vial. El reset de macros carga su propio bloque. Un reset completo ejecuta ambos **antes** de que Vial marque los datos como válidos. Los arranques con firma válida leen las ediciones guardadas. Detectar o forzar un perfil solo modifica RAM.

- TD0 conserva Shift al mantener y M0 al doble toque. M0 mantiene Caps Lock durante 100 ms. TD1/TD2 conservan MO(1/2) al mantener y TG(1/2) al doble toque, con 250 ms. La cuarta entrada vacía conserva 100 ms y las doce restantes, 200 ms.
- Se mantienen los 16 registros de Key Override, tres habilitados, con sus máscaras de capa y modificadores. Se conservan las 16 ranuras de macro. El archivo exportado tiene cero combos y ninguna asignación MT/LT explícita. El comportamiento tap/hold que usa este diseño proviene de Tap Dance.
- El ATmega32U4 tiene 1.024 bytes de EEPROM. En este build el mapa ocupa 480 bytes, Tap Dance 160 y overrides 160. Después de esos datos y de las cabeceras quedan 183 bytes para macros. El valor anterior de 512 podía alcanzar direcciones fuera de la EEPROM. Se mantienen las direcciones iniciales, se usa la capacidad física restante y los tres comandos exportados ocupan 49 bytes con sus terminadores.
- Para recuperar **tus cambios**, abrí el `.vil` de respaldo mediante **File → Load saved layout**, desbloqueá el teclado si Vial lo pide y verificá las capas, macros, Tap Dance y overrides.
- Para recuperar **la configuración incorporada** de forma intencional, respaldá primero y asigná temporalmente `EE_CLR` (Clear EEPROM) a una posición libre desde Vial. Pulsarla reinicializa la configuración y quita esa asignación temporal. Tras el reinicio, las cuatro capas y las tablas vuelven a los valores del firmware.
- Para futuras versiones, revisá la firma en `eeprom_version.h` si cambian offsets, tamaños, número de capas, UID o formato de Vial. Reutilizar la firma con una estructura incompatible puede interpretar datos viejos como otro tipo.

## OLED y validación

Ambos OLED permanecen encendidos durante la inactividad (`OLED_TIMEOUT 0`) mientras el teclado recibe alimentación.

El OLED izquierdo muestra el perfil arriba (MAC, NO MAC o DEFAULT) y cinco líneas de texto: SHIFT, CONTROL, ALT, CMD o WKEY, y CAPS. WKEY identifica el modificador GUI cuando el perfil efectivo es NO MAC. El texto se invierte al activar cada modificador; CAPS sigue el estado de bloqueo informado por el host. Solo se actualizan las líneas que cambian. El OLED derecho conserva los cuatro indicadores de capa.

| Verificación realizada | Resultado |
|---|---|
| Build AVR con LTO y comprobación de tamaño de Caterina | 25.332 / 28.672 bytes de flash de aplicación, 3.340 libres |
| SRAM según el ELF | 212 bytes de datos + 1.361 de BSS = 1.573 / 2.560 bytes. Quedan 987 para pila y uso dinámico; el pico real requiere hardware |
| Datos del HEX comparados con el .vil por dirección de símbolo del ELF | 240 posiciones, 4 entradas de Tap Dance específicas, 16 overrides y 49 bytes de macros coinciden. Las demás entradas usan los valores vacíos del fork |
| Definición Vial generada | Se descomprimió y coincidió con vial.json, incluidas las cuatro teclas User |
| Selección de perfiles | 24 casos con los tipos del fork: cuatro modos × cinco OS conocidos por la API y un valor fuera del enum |
| Inicialización y archivado | El ELF contiene la firma estable y la llamada de reset condicionada por la validación de EEPROM. La copia fechada coincide byte a byte con la salida de QMK |

Para repetir la prueba de perfiles desde esta carpeta:

```sh
cc -std=c11 -Wall -Wextra -Werror -I. -I/Users/manuel/vial-qmk/quantum \
  -I/Users/manuel/vial-qmk/tmk_core/protocol tests/profiles_test.c -o /tmp/lily58-profiles-test
/tmp/lily58-profiles-test
```

**Pendiente en el teclado:** comprobar enumeración real en los hosts de interés, intercambios y selección manual, ambas pantallas incluida suspensión/reactivación, comunicación entre mitades, reproducción de macros, overrides y tiempos de Tap Dance. Para verificar persistencia, cambiá una celda libre en Vial, reconectá y comprobá que siga asignada. Probá un reset completo solo cuando quieras descartar esa configuración y ya tengas el respaldo.
