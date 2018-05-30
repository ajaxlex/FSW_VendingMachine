Source files for the Ithaca Free Science Workshop's vending machine project.


Hardware configuration consists of the following:

* first Arduino - "Coin Handler" - running VendingMachineMain
* second Arduino- "Motor Controller" - running MotorControllerMain
* electronic Coin Acceptor ( DG600F ) communicating in serial mode at 4800 baud
* 8 buttons for product selection ( pass thru 5v to to Coin Handler )
* "TIP 120 array" custom perfboard for motor control of product dispensers, connected "Motor Controller"
* 8 vending machine motors with swirly spirals attached connected to "TIP 120 Array"

BASIC LOGIC
-----------

"Coin Handler" receives button presses from end user who desires a product.
If user adds coins before selecting a product, then TODO_FEEDBACK_CHOOSE_PRODUCT_FIRST
If there is no more of the product, then TODO_FEEDBACK_NO_MORE_GOODY
If there are not enough credits recorded for a product, then TODO_FEEDBACK_ADD_MORE_COINS
If there are enough credits, then DISPENSE_PRODUCT and REJECT_MORE_COINS
TODO establish timeouts for when to resume waiting for new request
TODO establish way for unused coins to be returned


PSEUDOCODE
----------------

```
If a product is chosen by one of the 8 buttons,
  and there are still some of that product left,
    and enough coins have been added to purchase it,

      "Coin Handler" sends a serial message at 4800 baud to "Motor Controller"
      the message will specify which product shall be dispensed

      "Motor Controller", when it receives a command to dispense a product, will set a pin HIGH
      corresponding to the motor it needs to activate for a set amount of timeouts
```

TODO - programming the boards should be easy!  ensure that the boards are clearly labeled
and that convenient USB cords are made available.


TODO - consider and attempt to account for edgecases for product dispense fail, etc.
