# Phomenix

A Phoenix webserver which uses websockets to send data to an ESP8266 which utilizes an IR blaster.

## Setting everything up

### To compile your Arduino code

The arudino code was created with the PlatformIO framework in VScode and it should be used and compiled that way as well.

You will need to declare variables in the `arduino/src/main.cpp` file or create a `arduino/lib/Config/Config.h` file and place the variables there. Here is an example of a `arduino/lib/Config/Config.h`:

```cpp
#define SSID "WiFi SSID"
#define PASSWORD "This is my awesome password"
#define WEBSOCKETURL "ws://192.168.0.102:4000/controller/websocket?secret_key=SECRET_SAYS_WHAT"
#define DEVICE_ID "living_room"
#define DEVICE_NAME "Backlight Table"
#define ORIGIN "https://192.168.0.102:4000"
```

The `Config.h` file is in `.gitignore` so I don't accidentally put my Server or WiFi credentials on the net.

## To setup your server variables

Once you've set the variables on the Arduino side, you'll need to set the secret key variable on the Phoenix side. For this just go to `config/config.exs` and edit the following:

```elixir
config :ex_led, ExLedWeb.ControllerSocket,
  secret_auth_key: "SECRET_SAYS_WHAT"
  ```

With the secret key you want to use.

## To start your Phoenix server

* Install dependencies with `mix deps.get`
* Install Node.js dependencies with `cd assets && npm install`
* Start Phoenix endpoint with `mix phx.server`

Now you can visit [`localhost:4000`](http://localhost:4000) from your browser.

Ready to run in production? Please [check our deployment guides](https://hexdocs.pm/phoenix/deployment.html).

## Sending custom codes
Currently the code works by extracting the HEX IDs of `button.controller-button#hex-code`.

An example of a button which send the hex code `0xF0F` would be:
```html
<button class="controller-button" id="0xF0F">Custom button</button>
```

Or you can use Emmet to generate it: `button.controller-button#0xF0F`, and then set the button text.

## Codes
I've found this snipped of code which has the correct HEX values for the IR data. It's for both the 24 and 44 button remote but I only had a 24 button reciever here.

```cpp
#define	key24  true
#define	key44  false


#if key24
#define	IR_BPLUS  0xF700FF	// 
#define	IR_BMINUS 0xF7807F	// 
#define	IR_OFF 	  0xF740BF	// 
#define	IR_ON 	  0xF7C03F	// 
#define	IR_R 	  0xF720DF	// 
#define	IR_G 	  0xF7A05F	// 
#define	IR_B 	  0xF7609F	// 
#define	IR_W 	  0xF7E01F	// 
#define	IR_B1	  0xF710EF	// 
#define	IR_B2	  0xF7906F	// 
#define	IR_B3	  0xF750AF	// 
#define	IR_FLASH  0xF7D02F	// 
#define	IR_B4	  0xF730CF	// 
#define	IR_B5	  0xF7B04F	// 
#define	IR_B6	  0xF7708F	// 
#define	IR_STROBE 0xF7F00F	// 
#define	IR_B7	  0xF708F7	// 
#define	IR_B8	  0xF78877	// 
#define	IR_B9	  0xF748B7	// 
#define	IR_FADE   0xF7C837	// 
#define	IR_B10	  0xF728D7	// 
#define	IR_B11	  0xF7A857	// 
#define	IR_B12	  0xF76897	// 
#define	IR_SMOOTH 0xF7E817	// 
#endif

#if key44
#define	IR_BPlus  0xFF3AC5	// 
#define	IR_BMinus 0xFFBA45	// 
#define	IR_ON 	  0xFF827D	// 
#define	IR_OFF 	  0xFF02FD	// 
#define	IR_R 	  0xFF1AE5	// 
#define	IR_G 	  0xFF9A65	// 
#define	IR_B  	  0xFFA25D	// 
#define	IR_W 	  0xFF22DD	// 
#define	IR_B1	  0xFF2AD5	// 
#define	IR_B2	  0xFFAA55	// 
#define	IR_B3	  0xFF926D	// 
#define	IR_B4	  0xFF12ED	// 
#define	IR_B5	  0xFF0AF5	// 
#define	IR_B6	  0xFF8A75	// 
#define	IR_B7	  0xFFB24D	// 
#define	IR_B8	  0xFF32CD	// 
#define	IR_B9	  0xFF38C7	// 
#define	IR_B10	  0xFFB847	// 
#define	IR_B11	  0xFF7887	// 
#define	IR_B12	  0xFFF807	// 
#define	IR_B13	  0xFF18E7	// 
#define	IR_B14	  0xFF9867	// 
#define	IR_B15	  0xFF58A7	// 
#define	IR_B16	  0xFFD827	// 
#define	IR_UPR 	  0xFF28D7	// 
#define	IR_UPG 	  0xFFA857	// 
#define	IR_UPB 	  0xFF6897	// 
#define	IR_QUICK  0xFFE817	// 
#define	IR_DOWNR  0xFF08F7	// 
#define	IR_DOWNG  0xFF8877	// 
#define	IR_DOWNB  0xFF48B7	// 
#define	IR_SLOW   0xFFC837	// 
#define	IR_DIY1   0xFF30CF	// 
#define	IR_DIY2   0xFFB04F	// 
#define	IR_DIY3   0xFF708F	// 
#define	IR_AUTO   0xFFF00F	// 
#define	IR_DIY4   0xFF10EF	// 
#define	IR_DIY5   0xFF906F	// 
#define	IR_DIY6   0xFF50AF	// 
#define	IR_FLASH  0xFFD02F	// 
#define	IR_JUMP3  0xFF20DF	// 
#define	IR_JUMP7  0xFFA05F	// 
#define	IR_FADE3  0xFF609F	// 
#define	IR_FADE7  0xFFE01F	// 
#endif
```

## Learn more

  * Official website: https://www.phoenixframework.org/
  * Guides: https://hexdocs.pm/phoenix/overview.html
  * Docs: https://hexdocs.pm/phoenix
  * Forum: https://elixirforum.com/c/phoenix-forum
  * Source: https://github.com/phoenixframework/phoenix
  * Remote codes: http://woodsgood.ca/projects/2015/02/13/rgb-led-strip-controllers-ir-codes/
