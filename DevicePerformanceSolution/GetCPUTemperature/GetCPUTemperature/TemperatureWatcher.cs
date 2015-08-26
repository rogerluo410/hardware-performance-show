using OpenHardwareMonitor.Hardware;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace GetCPUTemperature
{
    public class TemperatureWatcher
    {

        public float LastMeasuredTemperature { get; private set; }

        public TemperatureWatcher()
        {

        }

        public void Start()
        {
            watch();
        }

        private void watch()
        {
            var sensors           = CpuSensorsFilter.Instance.filter(SensorType.Temperature);
            float avgTemperature  = 0;
            var validSensorsCount = 0;
            foreach (var sensor in sensors)
            {
                if (sensor.Value != null)
                {
                    avgTemperature += sensor.Value.GetValueOrDefault();
                    validSensorsCount++;
                }
            }

            avgTemperature /= validSensorsCount;

            LastMeasuredTemperature = avgTemperature;

        }

    }
}
