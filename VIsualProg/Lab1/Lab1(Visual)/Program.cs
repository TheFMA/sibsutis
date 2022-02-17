using System;
using System.Collections.Generic;
using System.Linq;

namespace MyApp
{
    public class Program
    {
        public static void Main(string[] args)
        {
            int[] customerses = { 4, 6, 3, 8, 12, 2, 7 };
            long t = HW1.QueueTime(customerses, 3);
            Console.WriteLine($"Time = {t}");
        }

        public class HW1
        {
            public static long QueueTime(int[] customers, int n)

            {
                long time = 0;
                long min = 0;
                long[] endtime = new long[n];
                long[] tmp = new long[n];
                if (n == 1)
                {
                    for (int i = 0; i < customers.Length; i++)
                    {
                        time += customers[i];
                    }
                }
                else
                {


                    for (int i = 0; i < n; i++)
                    {
                        endtime[i] = customers[i];
                        tmp[i] = customers[i];
                    }
                    for (int i = n; i < customers.Length; i++)
                    {
                        min = tmp[0];
                        int min_index = 0;
                        for (int j = 1; j < n; j++)
                        {
                            if (min > tmp[j])
                            {
                                min = tmp[j];
                                min_index = j;
                            }
                        }
                        if (min == tmp[0])
                        {
                            min_index = 0;
                        }
                        endtime[min_index] += customers[i];
                        tmp[min_index] += customers[i];
                        for (int j = 0; j < n; j++)
                        {
                            tmp[j] -= min;

                        }
                    }
                }
                long end_max = endtime[0];
                for (int i = 1; i < n; i++)
                {
                    if (end_max < endtime[i])
                    {
                        end_max = endtime[i];
                    }
                }
                time = end_max;
                return time;
            }
        }
    }
}
