# CSE176e Quad Remote

## Assembly

## Parts

| desc               | url                                                                                                   | qty     | Notes |  
|--------------------|-------------------------------------------------------------------------------------------------------|---------|-----|
| 3mm plywood        | https://www.amazon.com/Premium-Baltic-Birch-Plywood-Woodpeckers/dp/B01MSWYF8N)                        | varies  | |
| Left cheap gimbal  | https://hobbyking.com/en_us/turnigy-9x-9ch-transmitter-replacement-throttle-rudder-gimbal-1pc.html    |   1     | |
| Right cheap gimbal | https://hobbyking.com/en_us/turnigy-9x-9ch-transmitter-replacement-elevator-aileron-gimbal-1pc.html   |   1     ||
| Nice gimbal        | https://hobbyking.com/en_us/frsky-replacement-gimbal-for-taranis-transmitter.html                     |   2     ||
| Gimbal screws      | https://www.mcmaster.com/90272a088                                                                    |   8     ||
| Board screws       | https://www.mcmaster.com/cadinlnord/91772a082                                                         |   4     ||
| Nuts               | https://www.mcmaster.com/90480a003                                                                    |   12    | |
| Sevro wires        | https://www.amazon.com/gp/product/B01J81HQ9Y/ref=oh_aui_search_asin_title?ie=UTF8&psc=1               |   2     |  for cheap servos|
| Battery Cable      |                                                                                                       |   1     ||
## Laser Cutting

The plywood base and the "donuts" used for standoffs are all in the
`.brd` file.  Open it, hide everything but the `baseplate` layer.
Print it to a PDF and feed it to your laser cutter.

The wooden parts are cut from 3mm plywood (see parts list).

## The Gimbals

long screws
8 donuts.

### Turnigy Gimbals

You'll need to add cables.  Cut the servo cables in half, strip the
tip of the wires, and solder them to the leads on the gimbals.  Some
hot glue or heat-shrink tubing will help stabilize the solder joint.

The critical thing is that the middle (red on the cables we use) wire
go to middle terminal.  The polarity of the other two can be fixed in
software.

For cheap ones, the gimbal with the non-returning up-down axis goes on
the right (next to the USB).

### Frsky

There is no difference between left and right, but you can configure
the throttle axis to be non-returning using the screws on the
underside of the gimbal.

## Board

5/8" screws.
3 donuts

## Connect Servos (Turnigy)

The headers are under the board and accsible through the windows in
the base plate.  The silkscreen has orientation information
('white'/'red', '+'/'-', and 'h' and 'v' for horizontal and vertical
axes).  However, if you get this wrong, you can fix it in software.


## Connect Servos (Frsky) 

Plug the wide header into the PCB.  You can trim off the other connectors, if you want.

## Battery Cable

Red is positive.

Attach the battery and tuck it under the board.  You can trim the battery cable, if you want.  Experimen with different lengths.

