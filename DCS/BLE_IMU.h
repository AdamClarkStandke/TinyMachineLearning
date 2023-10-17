#include <Arduino_BMI270_BMM150.h>

class MyBoschSensor: public BoschSensorClass {

  public:
    MyBoschSensor(TwoWire& wire = Wire) : BoschSensorClass(wire) {};

  protected:
    virtual int8_t configure_sensor(struct bmi2_dev *dev)
    {
      int8_t rslt;
      uint8_t sens_list[2] = { BMI2_ACCEL, BMI2_GYRO };

      struct bmi2_int_pin_config int_pin_cfg;
      int_pin_cfg.pin_type = BMI2_INT1;
      int_pin_cfg.int_latch = BMI2_INT_NON_LATCH;
      int_pin_cfg.pin_cfg[0].lvl = BMI2_INT_ACTIVE_HIGH;
      int_pin_cfg.pin_cfg[0].od = BMI2_INT_PUSH_PULL;
      int_pin_cfg.pin_cfg[0].output_en = BMI2_INT_OUTPUT_ENABLE;
      int_pin_cfg.pin_cfg[0].input_en = BMI2_INT_INPUT_DISABLE;

      struct bmi2_sens_config sens_cfg[2];
      sens_cfg[0].type = BMI2_ACCEL;
      sens_cfg[0].cfg.acc.bwp = BMI2_ACC_NORMAL_AVG4;
      sens_cfg[0].cfg.acc.odr = BMI2_ACC_ODR_400HZ;
      sens_cfg[0].cfg.acc.filter_perf = BMI2_PERF_OPT_MODE;
      sens_cfg[0].cfg.acc.range = BMI2_ACC_RANGE_16G;
      sens_cfg[1].type = BMI2_GYRO;
      sens_cfg[1].cfg.gyr.filter_perf = BMI2_PERF_OPT_MODE;
      sens_cfg[1].cfg.gyr.bwp = BMI2_GYR_NORMAL_MODE;
      sens_cfg[1].cfg.gyr.odr = BMI2_GYR_ODR_400HZ;
      sens_cfg[1].cfg.gyr.range = BMI2_GYR_RANGE_2000;
      sens_cfg[1].cfg.gyr.ois_range = BMI2_GYR_OIS_2000;
      sens_cfg[1].cfg.gyr.noise_perf = 1; 

      rslt = bmi2_set_int_pin_config(&int_pin_cfg, dev);
      if (rslt != BMI2_OK)
        return rslt;

      rslt = bmi2_map_data_int(BMI2_DRDY_INT, BMI2_INT1, dev);
      if (rslt != BMI2_OK)
        return rslt;

      rslt = bmi2_set_sensor_config(sens_cfg, 2, dev);
      if (rslt != BMI2_OK)
        return rslt;

      rslt = bmi2_sensor_enable(sens_list, 2, dev);
      if (rslt != BMI2_OK)
        return rslt;

      return rslt;
    }
};

void initIMU();
void calcIMU();
