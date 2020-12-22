#include "sensor.h"

struct AccelData
{
    float x = 0;
    float y = 0;
    float z = 0;
};

class AccelSensor: public Sensor {
  unsigned long time = 0;
  unsigned int count = 0;
  AccelData calibrate_sum;
  AccelData offset;
public:
  bool init() override;
  void read(float *x, float *y, float *z) override;
  bool calibrate() override;
};