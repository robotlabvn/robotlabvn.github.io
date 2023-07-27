---
layout: post
category: blog
title: Quadrotor connectors galore
snippet: A short guide to wire connectors for UAVs, for interfacing with power/pixracer/ESCs/motors, etc.
tags: [robotics, hardware]
---

A short guide to wire connectors for UAVs, for interfacing with power/pixracer/ESCs/motors, etc.

# Terminology

the **pitch** refers to the distance from one pin to another.

{% include image.html url="/assets/2020-08-13-connectors-galore/jst-sh-pitch.jpeg"
  description="A JST-SH 3-pin plug with 1.0mm pitch shown."
  width="30%" %}

The **wire size** (measured in American Wire Gauge AWG) determines the size of the wire that can be accommodated in the connector housing. The higher the number, the thinner the wire.

**JST** refers to Japan Solderless Terminal, which refers to a family of specific types of terminals. Wikipedia has a [detailed list](https://en.wikipedia.org/wiki/JST_connector) of them. One thing to note is that not all white terminals on a PCB are JST connectors, as we will see below...

# Wire to board connectors


| Name                     | pitch              | Current (Amp) | Voltage (V) | Wire size (AWG) | Pins     | Lock | Uses                                               | Image |
|--------------------------|--------------------|---------------|-------------|-----------------|----------|------|----------------------------------------------------|-------|
| JST GH [(info)](http://www.jst-mfg.com/product/detail_e.php?series=105/)                   | 1.25 mm (0.049 in) |             1 |          50 | 26 - 30        | variable | Yes  | Pixracer                                           | <img src="/assets/2020-08-13-connectors-galore/jst-gh.png" style="width:150px;"> |
| JST SH [(info)](http://www.jst-mfg.com/product/detail_e.php?series=231)                   | 1.00 mm (0.039 in) |             1 |          50 | 28 - 32        | variable | No   | Flight Controllers, RC Receivers, Video Transmitters | <img src="/assets/2020-08-13-connectors-galore/jst-sh.jpg" style="width:150px;">   |
| Molex Picoblade [(info)](https://www.molex.com/molex/products/family/picoblade)          | 1.25mm             |             1 |         125 | 26 - 32         | variable | No   | J121 auvidea TX2 connector board, amongst others    | <img src="/assets/2020-08-13-connectors-galore/pico.jpeg" style="width:150px;">   |
| JST XH [(info)](http://www.jst-mfg.com/product/detail_e.php?series=277)                   | 2.5mm              |             3 |         250 | 22 - 30      |      3-7 | No   | Balance plugs for batteries                        | <img src="/assets/2020-08-13-connectors-galore/jst-xh.png" style="width:150px;">      |
| DF13 [(info)](https://www.hirose.com/product/series/DF13?lang=en#)                    | 1.25mm             |             1 |          30 | 26 - 30       | variable |      | Pixhawk connector                                  | <img src="/assets/2020-08-13-connectors-galore/DF13.jpg" style="width:150px;">      |


# Wire to wire connectors

| Name                     | pitch              | Current (Amp) | Voltage (V) | Wire size (AWG) | Pins     | Lock | Uses                                               | Image |
|--------------------------|--------------------|---------------|-------------|-----------------|----------|------|----------------------------------------------------|-------|
| JST RCY [(info)](https://www.jst-mfg.com/product/detail_e.php?series=521)                  | 2.5mm              |             3 |         250 | 28-22           |        2 | Yes  | ESCs, LED Strips                                   | <img src="/assets/2020-08-13-connectors-galore/jst-rcy.jpeg" style="width:150px;">   |
| Dupont black connectors  | 2.54mm (0.1 in)    |               |             |                 | variable |      |                                                    |<img src="/assets/2020-08-13-connectors-galore/dupont.jpg" style="width:150px;">    |
| XT30                     | 2mm                |            15 |         500 |              18 |        2 |      | Battery connector                                  | <img src="/assets/2020-08-13-connectors-galore/xt30.jpg" style="width:150px;">   |
| XT60                     | 2.5mm              |            30 |         500 |              12 |        2 |      | Battery connector                                  | <img src="/assets/2020-08-13-connectors-galore/xt60.webp" style="width:150px;"> |
| XT90                     |                    |            40 |         500 |              10 |        2 |      | Battery connector                                  | <img src="/assets/2020-08-13-connectors-galore/xt90.jpg" style="width:150px;">  |



#### JST XH
these are almost exclusively now used for the balance plugs on the batteries.  The number of pins/wires is X+1 where X is the number of cells. So 2S batteries should have a balance plug with 3 pins, 3S will have 4 pins, etc.

{% include image.html url="/assets/2020-08-13-connectors-galore/balance-plug.png"
  description="A 4S LiPo battery with an XT60 male connector and a 5-pin JST XH balance plug."
  width="40%" %}

#### Dupont connectors
The dupont connector are just a colloquial name for black pin header connectors. They are difficult to find, since "Dupont" isn't the universal name for them.

#### XT series
the number following XT refers to the max current that can be put through these connectors

--------------

# How to tell them apart?

1. **JST GH** and **Molex Picoblade** are often confused as they have the same pitch. However, the GH has a clip that should lock into its housing on the board with a satisfying *click*, and the Molex Picoblade does not.

2. **Molex Picoblade** and **DF13** are often confused as well, since they have the same pitch and looks like they could fit in the same connector housing. However, the DF15 has a row of tiny slits at the bottom of the connectors, and should not fit into a Molex Picoblade housing easily, and vice versa.

3. The **JST SH** should look like a smaller version of the **Molex Picoblade**, because of the pitch differences.

4. **JST XH** has two clips that are arrow-like at the top of the male connector. Those clips should allow it to snap into the connector housing on the balance board of the battery charger.

5. **The XT30/60/90** connectors will have its type etched onto the connector, as shown in the photos.

{% include image.html url="/assets/2020-08-13-connectors-galore/xt30-60-90.jpg"
  description="Obvious size differences between xt30, xt60, xt90"
  width="40%"
%}

6. Sometimes, you just need to stare at all of them at once to figure out which one is yours. The following pictures are shamelessly scraped through the web:

<div class="col">
{% include image.html url="/assets/2020-08-13-connectors-galore/sh-pico-zh-xh.jpg"
  description=""
  width="80%"
%}
</div>
<div class="row">
<div class="col">
{% include image.html url="/assets/2020-08-13-connectors-galore/sh-pico-xh.jpeg"
  description=""
  width="100%"
%}
</div>
    <div class="col">
    {% include image.html url="/assets/2020-08-13-connectors-galore/sh-pico-zh-xh.jpeg"
      description=""
      width="100%"
    %}
    </div>

</div>
