# Blauberg_S14

Blauberg S14 replacement controller with ESPHome

With this library you can replace the S14 controller of your air recuperator (mine is KOMFORT ERV EC DB 350) and control it via ESPHome.

![](/images/home_assistant_1.png)
![](/images/home_assistant_2.png)
![](/images/controller.jpg)


## Connection

```
 Wire from              LM2596                    D1 Mini          1000uf capacitor (optional)
 original controller

+24V (Yellow)   --------> V in+  ---> V out+ ---> 5V
RX (Green)      --------------------------------> GPIO3 (RX)
TX (Brown)      --------------------------------> GPIO1 (TX)
GND (White)     --------> V in- ----> V out- ---> GND  <---------- negative lead
                                                  3.3V <---------- positive lead
```
I used DC/DC Buck Converter LM2596 to step down +24V to +5V and power up D1 mini.
Optional, I connected 1000uF to 3.3V pin of D1 mini. It will make voltage of controller more stable, but it is not required.

In case of using external power supply, please check first, that there is no voltage between air recuperator ground and power supply ground (ground loop). **Otherwise it will fry something.**

**Keep in mind, that your pinout can be different, so double check.**

![](/images/original_controller_1.jpg)

![](/images/original_controller_2.jpg)

![](/images/original_controller_3.jpg)

## Box

I created custom box to 3d print for this controller. STL files are in box directory.
My pcb dimensions are 50mm x 70mm

![](/images/box.png)

## HomeAssistant automations

Set max speed, when humidity in one of rooms rises above 55% (for at least 10 seconds) and reset to previous speed when it drops below 55%
```
alias: Recuperator boost
description: ""
triggers:
  - value_template: >-
      {{ states('sensor.aqara_tualetas1_humidity') > '55' or
      states('sensor.aqara_tualetas2_humidity') > '55' }}
    for:
      hours: 0
      minutes: 0
      seconds: 10
    trigger: template
conditions: []
actions:
  - data:
      scene_id: recuperator_revert
      snapshot_entities:
        - fan.blauberg_s14_fan
    action: scene.create
  - action: fan.set_percentage
    metadata: {}
    data:
      percentage: 100
    target:
      entity_id: fan.blauberg_s14_fan
  - wait_template: >-
      {{ states('sensor.aqara_tualetas1_humidity') < '55' and
      states('sensor.aqara_tualetas2_humidity') < '55' }}
    continue_on_timeout: true
  - data: {}
    target:
      entity_id: scene.recuperator_revert
    action: scene.turn_on
mode: single
max_exceeded: silent
```

Toggle summer mode by outdoor temp
```
alias: Recuperator summer mode toggler
description: ""
triggers:
  - trigger: state
    entity_id:
      - sensor.aqara_kiemas_temperature
conditions: []
actions:
  - choose:
      - conditions:
          - condition: numeric_state
            entity_id: sensor.aqara_kiemas_temperature
            above: 10.5
          - condition: state
            entity_id: switch.blauberg_s14_summer_mode
            state: "off"
        sequence:
          - action: switch.turn_on
            metadata: {}
            data: {}
            target:
              entity_id: switch.blauberg_s14_summer_mode
      - conditions:
          - condition: numeric_state
            entity_id: sensor.aqara_kiemas_temperature
            below: 10
          - condition: state
            entity_id: switch.blauberg_s14_summer_mode
            state: "on"
        sequence:
          - action: switch.turn_off
            metadata: {}
            data: {}
            target:
              entity_id: switch.blauberg_s14_summer_mode
mode: single
```
