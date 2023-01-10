## Example Summary

This application demonstrates a USS SW example with UART support

## Peripherals & Pin Assignments


* `UART`      This interface is used to output the USS SW Library results (ATOF, DTOF, VFR)

## Board Resources & Jumper Settings
Please refer to the development board's Hardware User's Guide.

Python 3.X is required for this example. To install Python download the latest
version at https://www.python.org/downloads/release

## Example Usage

* Open a serial session (e.g. [`PuTTY`](http://www.putty.org/ "PuTTY's
Homepage"), etc.) to the appropriate COM port.
    * The COM port can be determined via Device Manager in Windows or via
`ls /dev/tty*` in Linux.

* The connection should have the following settings:
    ```
     Baud-rate:     115200
     Data bits:          8
     Stop bits:          1
     Parity:          None
     Flow Control:    None
    ```

* Run the USS SW Lib template example. It captures USS measurements once a second and sends the USS SW results via the UART peripheral. 

* Save the serial session data to a CSV file, and use the script below to convert the hexidecimal data to exponential format.

* The example uses a Python script to decode the hexidecimal result to exponential format. The UART parser script is found in **&lt;USS_INSTALL_DIR&gt;/tools/examples/uart_parse.py**

* Run the uart_parser python script

    ```
     python uart_parser.py <input_csv_file> <output_csv_file>
    ```