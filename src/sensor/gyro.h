#include "sensor.h"

struct GyroData
{
    float x = 0;
    float y = 0;
    float z = 0;
};

class GyroSensor: public Sensor {
  unsigned long time = 0;
  unsigned int count = 0;
  GyroData calibrate_sum;
  GyroData offset;
public:
  bool init() override;
  void read(float *x, float *y, float *z) override;
  bool calibrate() override;
};