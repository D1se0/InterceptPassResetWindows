# InterceptPassResetWindows Técnica

## 📖 Descripción

Esta herramienta implementa un **Password Filter** de Windows que intercepta y registra los cambios de contraseñas en el sistema. Utiliza una técnica legítima de Windows para monitorizar las modificaciones de credenciales en tiempo real.

## 🛠️ ¿Qué es un Password Filter?

Un **Password Filter** es un componente oficial de Windows que permite:
- Validar contraseñas contra políticas personalizadas
- Interceptar cambios de contraseñas antes de que se apliquen
- Registrar eventos de modificación de credenciales
- Implementar lógica personalizada durante el proceso de cambio

**Esta herramienta utiliza esta capacidad nativa de Windows para propósitos de auditoría y seguridad.**

## ⚙️ Requisitos del Sistema

- **Sistema Operativo**: Windows 10/11, Windows Server 2012+
- **Privilegios**: Ejecución como Administrador
- **Archivos necesarios**: 
  - `CreateInterceptPassChange.exe`
  - `scecIi.dll` (en el mismo directorio)

## 🚀 Instalación y Uso

### Paso 1: Ejecutar el Instalador

```cmd
.\CreateInterceptPassChange.exe
```

## Paso 2: Verificación Automática

El programa realizará automáticamente:

✅ Verificación de privilegios de administrador
✅ Detección del archivo DLL requerido
✅ Advertencia sobre compatibilidad con Windows 11

## Paso 3: Proceso de Instalación

Presiona ENTER para continuar. El instalador ejecutará:
Copia del DLL al System32

```cmd
copy .\scecIi.dll C:\Windows\System32\scecIi.dll
```

Modificación del Registro de Windows
Ruta: `HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Lsa`
Valor: `Notification Packages`
Se añade: `scecIi`

## Paso 4: Reinicio del Sistema

```cmd
¿Desea reiniciar ahora? (S/N): S
```

Es imprescindible reiniciar para que los cambios surtan efecto.

🔍 Verificación del Funcionamiento
Probar el Cambio de Contraseña

```cmd
# Cambiar contraseña de cualquier usuario
net user Administrador NuevaPassword123
```

# O mediante interfaz gráfica
# Panel de Control > Cuentas de Usuario > Cambiar contraseña
Verificar Captura de Credenciales

```cmd
# Comprobar el archivo de log local
type C:\LogFile.txt
```

# Ejemplo de salida esperada:
# DOMINIO\usuario : NuevaPassword123
# WORKGROUP\Administrador : NuevaPassword123

## 🔧 Estructura Técnica

Archivos Involucrados
Archivo	Propósito	Ubicación Final
scecIi.dll	DLL del Password Filter	`C:\Windows\System32\`
CreateInterceptPassChange.exe	Instalador	Directorio de ejecución
LogFile.txt	Log de credenciales	`C:\`
Entradas de Registro Modificadas

```
HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Lsa
└── Notification Packages (REG_MULTI_SZ)
    ├── scecli (nativo de Windows)
    └── scecIi (nuestro filter)
```

## ⚠️ Consideraciones Importantes

### Compatibilidad

Windows 10: Compatibilidad total
Windows 11: Puede presentar problemas de compatibilidad
Windows Server: Funciona correctamente en versiones 2012+

### Seguridad

✅ Solo captura cambios de contraseña, no credenciales existentes
✅ Funciona únicamente durante operaciones de cambio
✅ Requiere reinicio para activarse
✅ Necesita privilegios de administrador

### Legal y Ético

Esta herramienta está diseñada para:
Auditorías de seguridad autorizadas
Pruebas de penetración con consentimiento
Investigación forense legal
Entornos de laboratorio controlados

No utilizar para:

Actividades ilegales
Sin el consentimiento explícito del propietario del sistema
En sistemas de producción sin autorización

### 🐛 Solución de Problemas

Error: "No se encontró el archivo `scecIi.dll`"
Solución: Asegúrate de que el DLL esté en el mismo directorio que el ejecutable.

Error: "Acceso denegado"
Solución: Ejecuta como Administrador.

Las contraseñas no se capturan

Solución:

Verifica que el reinicio se realizó después de la instalación
Comprueba que el DLL está en `C:\Windows\System32\`
Verifica la entrada de registro en Notification Packages

Windows Defender bloquea la ejecución
Solución: Añade excepciones para ambos archivos en la protección en tiempo real.

## 🔄 Desinstalación

Eliminar la entrada scecIi de Notification Packages en el registro
Eliminar `C:\Windows\System32\scecIi.dll`
Eliminar `C:\LogFile.txt`
Reiniciar el sistema

## 📞 Soporte

Para problemas técnicos o preguntas sobre el uso ético de esta herramienta, consulta con el equipo de seguridad correspondiente.

> ⚠️ ADVERTENCIA: Esta herramienta debe usarse únicamente en entornos controlados y con el consentimiento explícito del propietario del sistema. El uso no autorizado puede violar leyes locales e internacionales.
