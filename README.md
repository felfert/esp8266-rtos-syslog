# A minimal implementation of syslog using UDP for ESP8266-RTOS

This repository is intended to be included as a component for ESP8266 projects
which use Espressif's ESP8266\_RTOS\_SDK.

To achieve this, you have 2 options:

 1. Offline: Copy this directory to <YourProject>/components/syslog
 2. Online: Add this repository as a submodule in your project.

## Configuration

This component provides several menuconfig settings. When running `make menuconfig`,
these can be found under `Component config` &rarr; `syslog`

To enable/disable the component, the `USE_SYSLOG` can be used. If disabled, all
syslog functions are replaced by NOPs.

This component requires using an event group which should be defined in your app.
In that event group, there should be 2 event bits that must be handled by your app:

 1. A `WIFI_CONNECTED` bit, that gets set, when Wifi has connected
 2. A `NTP_SYNCED` bit, thet gets set, when NTP has aquired the current time.

A third bit in the event group will be used by syslog itself.

The configuration lets you specify the name of the event group and the names of both
bit constants that are handled by your app. It also lets you define the value of the
`MSG_QUEUED` bit, that gets used by syslog itself.

The rest of the config settings should be self explanatory. If in doubt, use menuconfig's
help functionality.

## Regular Functionality

See syslog(3) openlog(3)and closelog(3)

## Non standard functionality

`void set_syslog_hostname(const char* hostname)` allows overriding the default hostname
which is taken from `CONFIG_LWIP_LOCAL_HOSTNAME`. Obviously, this should be called before
any other functions

`extern void syslogx(int __pri, const char* app, const char* __fmt, ...)` provides an
additional parameter `app` for overriding the syslog identifier.

`void vsyslogx(int __pri, const char* app, const char* __fmt, va_list alist)` provides an
additional parameter `app` for overriding the syslog identifier.

`void syslog_flush(void)` blocks, until all queued messages have been sent.

## Example
An example project that uses this component can be found [here](https://github.com/felfert/level-sensor).
