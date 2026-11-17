
/*
  Project: Marine Water Cleaning Robotic Boat
  Controller: ESP32-CAM (OV3660)
  AI Framework: Edge Impulse

  Function:
  Classifies floating waste into:
  1. plastic
  2. non-plastic

  Plastic     -> Send P to Arduino UNO
  Non-plastic -> Send NS to Arduino UNO

  NOTE:
  Replace the model header with the actual Edge Impulse
  generated header. Camera pin configuration and image
  preprocessing must match the actual ESP32-CAM board.
*/

#include <Arduino.h>
#include <string.h>

// Replace with your generated Edge Impulse model header.
// Example:
// #include <your_project_inferencing.h>

#define CONFIDENCE_THRESHOLD 0.70

#define SERIAL_BAUD_RATE 9600

// Classification labels
#define PLASTIC_LABEL "plastic"
#define NON_PLASTIC_LABEL "non-plastic"

// Send classification to Arduino UNO
void sendClassification(const char* result) {
    Serial.println(result);
}

// Process Edge Impulse classification results
void processClassification(ei_impulse_result_t result) {

    float plasticScore = 0.0;
    float nonPlasticScore = 0.0;

    for (size_t i = 0;
         i < EI_CLASSIFIER_LABEL_COUNT;
         i++) {

        const char* label =
            result.classification[i].label;

        float confidence =
            result.classification[i].value;

        if (strcmp(label, PLASTIC_LABEL) == 0) {
            plasticScore = confidence;
        }

        else if (strcmp(label, NON_PLASTIC_LABEL) == 0) {
            nonPlasticScore = confidence;
        }
    }

    if (plasticScore >= CONFIDENCE_THRESHOLD &&
        plasticScore > nonPlasticScore) {

        Serial.println("Plastic detected");
        sendClassification("P");

    }

    else if (nonPlasticScore >= CONFIDENCE_THRESHOLD &&
             nonPlasticScore > plasticScore) {

        Serial.println("Non-plastic detected");
        sendClassification("NS");

    }

    else {
        Serial.println("Uncertain object");
        sendClassification("UNKNOWN");
    }
}

void setup() {

    Serial.begin(SERIAL_BAUD_RATE);

    Serial.println();
    Serial.println("Marine Water Cleaning Robotic Boat");
    Serial.println("ESP32-CAM Object Classification");
    Serial.println("Edge Impulse Initialization");

}

void loop() {

    /*
      CAMERA CAPTURE AND EDGE IMPULSE INFERENCE

      1. Initialize the OV3660 camera.
      2. Capture an image.
      3. Convert the image into the format required
         by your Edge Impulse model.
      4. Run run_classifier().
      5. Pass the result to processClassification().

      These steps require your actual model library
      and camera configuration.
    */

    delay(1000);
}
