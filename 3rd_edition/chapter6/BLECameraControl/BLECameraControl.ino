// include libraries
#include <multiCameraIrControl.h>
#include <CurieBLE.h>


// initialize peripheral
BLEPeripheral blePeripheral;
// initialize the camera service and its UUID:
BLEService cameraService("F01A");
// initialize the shutter characteristic, its UUID and its properties:
BLEIntCharacteristic shutter("F01B", BLERead | BLEWrite);
// initialize the IR camera control:
Nikon camera(3);

void setup() {
  Serial.begin(9600);

  // set  local name for the peripheral and advertise the camera service:
  blePeripheral.setLocalName("irRemote");
  blePeripheral.setAdvertisedServiceUuid(cameraService.uuid());

  // add the service and characteristic as attributes of the peripheral:
  blePeripheral.addAttribute(cameraService);
  blePeripheral.addAttribute(shutter);

  // set the initial value for the characeristic:
  shutter.setValue(0);

  // begin advertising camera service:
  blePeripheral.begin();
  Serial.println("Starting");
}

void loop() {
  // poll the peripheral for activity:
//  blePeripheral.poll();

  // if a central wrote to the shutter characteristic:
  if (shutter.written()) {
    // and the characteristic's value is 1:
    if (shutter.value() == 1) {
      camera.shutterNow();        // send the IR signal
      Serial.println("click");
      shutter.setValue(0);        // reset the value to 0
    }
  }
}
