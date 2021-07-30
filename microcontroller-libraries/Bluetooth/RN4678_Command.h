// Created by Dante on 2/24/2021.
/*
 * This will document and define the necessary ASCII commands for the bluetooth module.
 * Effectively, this is a header-based re-creation of microchip's document DS50002506C.
 * "RN4678 Bluetooth Dual Mode Module Command Reference User’s Guide"
 * https://ww1.microchip.com/downloads/en/DeviceDoc/RN4678-Bluetooth-Dual-Mode-Module-Command-Reference-User-Guide-DS50002506C.pdf
 *
 * Best viewed in an IDE with code collapsing
 *
 * Modes of operation:
 * The RN4678 operates in two modes:
 * DATA MODE: the device acts as a data pipe, outputting UART data over SPP (classic) or UART
 * Transparent (LE). Received data is output directly to UART.
 * COMMAND MODE: The RN4678 uses ASCII commands over a UART to configure all of its bluetooth capabilities.
 * The commands themselves are split up into three groups:
 * SET commands configure the device, are non-volatile, and sometimes require a reboot to apply
 * GET commands return stored data on the device
 * ACTION commands perform actions, ie inquiry, connecting
 *
 * Only ACTION commands have no parameters (most of the time)
 * Only GET commands return values other than ERR# or AOK
 * Commands MUST be terminated by carriage return char, <\r> or <\0xd>
 * Commands and parameters are delimited with commas
 * Commands are case sensitive
 * Only send ONE command at a time
 * If the ESC character is sent (<0x1B>) all previous commands and
 * un-executed commands will be ignored
 *
 * If the device encounters an error, it will return ERR#, with the number representing:
 * 1: Error in command syntax
 * 2: Error in Parameter format or range
 * 3: Error in accepting command given current state
 * 4: Error in current settings
 *
 * Unless explicitly stated, all commands apply to both BR and LE
 *
 * Arguments are listed as <arg>. If pre+post-fixed with square brackets, then the argument is optional
 * <4-7> is between 4 to 7
 * <4,7> is either 4 or 7
 * [<4-7>] is an optional argument, from 4 to 7
 * The arg notation <Hn> means that the expected arg is n bits in Hex format, so H16 is four hex digits
 *
 * Due to the nature of the ASCII-based commands, all "ints" are actually their ASCII representations as chars
 */

#ifndef MICROCONTROLLER_LIBRARIES_RN4678_COMMAND_H
#define MICROCONTROLLER_LIBRARIES_RN4678_COMMAND_H

/******************************************************
* SET Commands
*******************************************************/
/* Set commands change the RN4678 configurations and take effect after rebooting via
 * R,1 command, hard Reset or power cycle. */

#define BT_SET_AUTH "SA,"               /* Args: <1-4>
                                         * Set authentication method with argument #:
                                         * 1 : SSP Pin Confirm: secure simple pairing, sends 6-digit pin to UART &
                                         *      device, looks for confirmation
                                         * 2 : SSP "Just works": no request to display or input any security pin
                                         * 3 : SSP Pin Input: 6-digit pin is sent to remote device, local RN4678 must
                                         *      input the pin
                                         * 4 : Legacy Pin Code: ONLY FOR BR, and is being phased out. Uses SP command to
                                         *      set pin */

#define BT_SET_SERVICE_CLASS_MSW "SC,"  /* Args: <H16>
                                         * BT CLASSIC ONLY: This command sets the “Service Class” field in the Class of
                                         * Device (COD). The service class consists of the 11 Most Significant bits in
                                         * the COD. This command sets the most significant word (msw) to create the
                                         * 24-bit device class number. The inquiring device interprets the service class
                                         * to determine the service. */

#define BT_SET_SERVICE_CLASS_LSW "SD,"  /* Args: <H16>
                                         * BT CLASSIC ONLY: The COD is a 24-bit number. The higher 8-bit value is set by
                                         * using the command SC and the lower 16-bit value is set by using the command
                                         * SD. */

#define BT_SET_DEVICE_MODEL "SDM,"      /* Args: <txt>
                                         * BLE ONLY: This command sets the model string in the BLE device information
                                         * service. It expects the model number string, max of 16 chars */

#define BT_SET_DEVICE_MFG "SDN,"        /* Args: <txt>
                                         * BLE ONLY: Sets the manufacturer string in the BLE device information service.
                                         * Max 16 chars. */

#define BT_SET_SW_VERSION "SDR,"        /* Args: <txt>
                                         * BLE ONLY: Sets the software version number of the firmware. Expects an ASCII
                                         * string up to four chars long. */

#define BT_SET_SERIAL_NO "SDS,"         /* Args: <txt>
                                         * BLE ONLY: Sets the serial number of the device. Expects up to 16 ASCII chars */

#define BT_SET_UUID "SE,"               /* Args: <H16>
                                         * CLASSIC ONLY: Sets the Universally Unique Identifier (UUID) for service
                                         * discovery process. ONLY supports the standard 16-bit UUID */

#define BT_SET_DEFAULTS "SF,"           /* Args: <1>
                                         * Resets to factory defaults */

#define BT_SET_MODE "SG,"               /* Args: <0-2>
                                         * Changes the bluetooth mode:
                                         * 0: Dual mode (default)
                                         * 1: Low Energy ONLY
                                         * 2: Classic ONLY */

#define BT_SET_LOW_POWER "SH,"          /* Args: <0,1>
                                         * Enables low-power operation
                                         * 0: use 32kHz clock in idle unless UART RX_IND pin is pulled low, switching to 16MHz
                                         * 1: use 16MHz clock in idle mode,UART is always operational */

#define BT_SET_INQUIRY_LEN "SI,"        /* Args: <H16>
                                         * CLASSIC ONLY: Set length of time device spends enabling inquiry scan. Min is
                                         * 0x0012, representing a 1% duty cycle. The page scan interval is fixed at 0x1000,
                                         * the default window is 0x0100. If the device is already paired, inquiry scan is
                                         * not used. */

#define BT_SET_PAGE_SCAN_LEN "SJ,"      /* Args: <H16>
                                         * CLASSIC ONLY: Set length of time device spends enabling page scanning. Min is
                                         * 0x0012, representing a 1% duty cycle. The page scan interval is fixed at 0x1000,
                                         * the default window is 0x0100. The max value is 0x800. Set arg to 0x0000 to disable
                                         * page scanning. */

#define BT_SET_SCAN_LEN "SL,"           /* Args: <H16>
                                         * Sets the duration of Classic and LE scan operation. Expects one 8bit arg in hex
                                         * format. Input indicates the scan duration in units of 10 seconds. Scan must be
                                         * between 01 and 06. Any input greater than 06 will be considered to last forever.
                                         * Scans can be terminated with 'x' command before timeout. */

#define BT_SET_ENA_RECONNECT "SM,"      /* Args: <0,6>
                                         * Set the reconnection mode
                                         * 0: Default mode
                                         * 6: Auto Reconnect mode */

#define BT_SET_NAME "SN,"                /* Args: <txt>
                                         * Command sets the device name, where <txt> is up to 16 alphanumeric chars.
                                         * By default, the device name is 'RN4678-b1b0' where b1 and b0 are the lower
                                         * order byte values of the device's BT address. */

#define BT_SET_DELIMITER "SO,"          /* Args: <txt1>, [<txt2>]
                                         * Sets the extended status string, where <txt1> and <txt2> delimit status strings
                                         * returned from the UART. The first arg is the prefix, and the second arg is the
                                         * suffix. ie, when a connection is established, the device sends
                                         * "<str1>CONNECT<str2>". Arg 2 is optional, and if no parameters are passed,
                                         * then all the status strings are suppressed, including the "Rebooting" string
                                         * as a response to 'R,1'. As well, the G0 command will return NULL.
                                         * Default is %,%
                                         * SEE TABLE 2-4 (T2-4) for list of status strings */

#define BT_SET_PIN "SP,"                /* Args: <txt>
                                         * This command sets the security pin code, where <txt> is either a 4 or 6 digit
                                         * numeric pin. 4 digit pins are used for legacy pin code pairing, while 6 digit
                                         * pins are used for SPP auth in BLE (if a fixed pin is desirable). The fixed 6
                                         * digit pin code in BLE is NOT supported by many BLE implementations. The user
                                         * must understand the security impact of using the fixed pin code under SPP mode. */

#define BT_SET_FEATURE "SQ,"            /* Args: <H16>
                                         * Sets the features of the module. Input <H16> is in the format of a bitmap,
                                         * interpolated according to table 2-5 (See T2-5 below). */

#define BT_SET_REMOTE_ADDR "SR,"        /* Args: [<0,1,z>], <txt>
                                         * The first argument is optional, and the second is a MAC address.
                                         * This command stores the remote address. When the MAC address is for a Classic
                                         * device, then ONLY the second argument should be entered (a 12hex/6byte address
                                         * without spaces or characters between digits. For BLE devices, the first argument
                                         * specifies address type, either public (0) or random (1), followed by the MAC
                                         * address. For BLE random addresses, the link-back feature may not work since the
                                         * BLE address might change when performing the link-back feature. As well, this
                                         * takes the the argument 'z' (and no mac address) to erase any stored address. */

#define BT_SET_SERVICE_NAME "SS,"       /* Args: <txt>
                                         * This command sets the service name for BT Classic, where <txt> can vary from
                                         * 1 to 16 alphanumeric chars. */

#define BT_SET_CONN_PARAMS "ST,"        /* Args: <H16>,<H16>,<H16>,<H16>
                                         * BLE ONLY: Sets the connection params for BLE. These are used for establishing
                                         * a connection when the module acts as a master device. Connection parameters
                                         * can be modified by Action command T after a connection is established.
                                         * This expects four 16-bit hex parameters:
                                         * Minimum connection interval (units of 1.25ms)
                                         * Maximum connection interval (units of 1.25ms)
                                         * Slave latency (unknown units)
                                         * Supervision timeout (units of 10ms) */

#define BT_SET_SLEEP_TIMER "STO,"        /* Args: <H8>
                                         * Sets the power on standby timeout. The timeout is in units of 10.24 seconds.
                                         * The module will go to Deep Sleep mode after the timeout and consumes least
                                         * possible current. Pulling the WAKE_UP pin low will bring the module out of
                                         * Deep Sleep mode. */

#define BT_SET_DISCONNECT_SLEEP_TIMER "STD," /* Args: <H8>
                                         * Sets the disconnect standby timeout. The timeout is in units of 10.24 seconds.
                                         * The module will go to Deep Sleep mode after the timeout from a disconnect
                                         * event. in this mode the module consumes the least possible current. Pulling
                                         * the WAKE_UP pin low will bring the module out of this Deep Sleep mode. */

#define BT_SET_UART_BAUD "SU,"          /* Args: <H8>
                                         * Sets the UART baud rate. Refer to table 2-6 (T2-6 below) for input params and
                                         * their corresponding rates.
                                         * 0x03 = 115200 */

#define BT_SET_SNIFF_RATE "SW,"         /* Args: <H16>
                                         * CLASSIC ONLY: This command enables low-power sniff. In this mode, the device
                                         * enters a deep sleep and wakes up every 625us * <H16> to send/receive data.
                                         * For example, 'SW,0050' causes the module to enter low-power sleep and wake
                                         * once every 50ms to check for RF activity. This setting is useful for
                                         * applications in which the device is connected and sending data. Data is not
                                         * lost, but delayed. Default is 0x0000 */

#define BT_SET_PIN_CONFIG "SX,"         /* Args: <H8>,<H8>
                                         * Sets the functions of individual pins available on the module. It expects
                                         * two 1-byte inputs. The first indicates the pin and the second indicates the
                                         * function to be assigned to the pin. Refer to tables 2-7 and 2-8.
                                         * See T2-7 and T2-8 below. */

#define BT_SET_TX_POWER "SY,"           /* Args: <0-4>
                                         * This command sets the transmit power of the module */

#define BT_SET_BeaconThings "SZ,"       /* Args: <0-1>
                                         * BLE ONLY: Controls the BeaconThings feature of the module. A single digit
                                         * input parameter is expected. If 1, the BeaconThings feature is enabled. If 0,
                                         * the feature is disabled. */

#define BT_SET_HUMAN_NAME "S-,"         /* Args: <txt>
                                         * Sets the serialized friendly name of the device, where <txt> can be up to 11
                                         * alphanumeric characters. This command automatically appends the last two
                                         * bytes of the BT MAC address to the name, which is useful for generating a
                                         * custom name with unique numbering. */

#define BT_SET_ROLE_SWITCH "S?,"        /* Args: <0,1>
                                         * CLASSIC ONLY: Role Switch command enables and disables the role switch, where
                                         * an input parameter of 0 disables role switch, and 1 enables it. If the switch
                                         * is set when a device in Default mode is receiving an incoming connection, the
                                         * device tries to force a role switch, enabling the slave to become the master.
                                         * This option is useful in situations where the local device sends high-speed
                                         * data up to the remote host, and can improve performance. While connected to
                                         * the local device, the connected host may NOT be able to make additional
                                         * outbound (multi-point) connections. */

#define BT_SET_CONFIG_DETECT_CHAR "S$," /* Args: <char>
                                         * Sets the configuration detect character string, where <char> is a single
                                         * character. This setting configures the escape character to enter Command
                                         * mode (default is $). Factory defaults will return the device to use $ as the
                                         * escape character. */


// Table T2-4: LIST OF STATUS STRINGS
/* STATUS           : Description
 * AUTHENTICATED    : BT classic iAP auth success
 * AUTH_FAIL        : BT classic iAP auth failure
 * BONDED           : New bonding information saved
 * CONNECT          : Device connected with peer
 * DISCONN          : Device disconnect from peer
 * END_INQ          : End of BT classic inquiry
 * END_SCN          : End of BLE scan
 * ERR_CONN         : Connection attempt fails
 * ERR_CONN_PARAM   : BLE fails to update connection parameters
 * ERR_LSEC         : BLE security failure
 * ERR_SEC          : BT Classic security failure
 * FACTORY_RESET    : Factory reset triggered by factory reset pin in the first 5 seconds of power on
 * LBONDED          : BLE saved linked key
 * LSECURED         : BLE secured link
 * LSECURE_FAIL     : BLE security failure
 * LSTREAM_OPEN     : BLE UART Transparency stream open
 * MLDP_MODE        : RN4020 MLDP service detected
 * REBOOT           : RN4678 reboot
 * RFCOMM_CLOSE     : SPP stream service deactivated
 * FRCOMM_OPEN      : SPP stream service activated
 * SECURE_FAIL      : BT Classic security failure
 * SESSION_CLOSE    : BT Classic iAP data session close
 * SESSION_OPEN     : BT Classic iAP data session open
 * SECURED          : BT Classic secured link
 * IAP1_DISABLED    : If a peer device tries to connect via iAP1 when module has iAP1 feature disabled
 *
 * Note: See set command SO. each status string will be bookended with the characters set with that command.
 */

// Table T2-5: FEATURE SET BITMAPS for command "SQ"
/* Bit Map  : Feature
 * 0x8000   : If set, the module is put into fast mode, where Command mode entry is no longer available to put the
 *          :   device into command mode. The CMD/Data switch pin defined in command SX controls the device operation mode
 * 0x4000   : If set, NO prompt "CMD>" is required when RN4678 is ready to accept a new command
 * 0x2000   : If set, NO ack. is required for UART transparent under BLE connection
 * 0x1000   : If set, the hardware flow control for UART is enabled. Flow control is enabled by default
 * 0x0800   : If set, NO non-connectable beacon shows up in the BLE scan result
 * 0x0400   : If set, NO connectable advertisement shows up in the BLE scan result
 * 0x0200   : If set, RN4678 does NOT filter out duplicate BLE scan results. Set this bit if the module expects to see
 *          :   dynamically changing advertisements
 * 0x0100   : If set, the module performs passive scan instead of default active scan
 * 0x0080   : If set, the module reboots after disconnection
 * 0x0008   : If set, the SW_BTN functionality is enabled. By default it is disabled.
 *
 * Example: SQ,9080 enters fast mode, enables flow control, and enables reboot after disconnect
 */

// Table T2-6: UART BAUD RATES for command "SU"
/* Byte : Baud Rate
 * 03   : 115200
 * 04   : 57600
 * 05   : 38400
 * 06   : 28800
 * 07   : 19200
 * 08   : 14400
 * 09   : 9600
 * 0A   : 4800
 * 0B   : 2400
 * 10   : 307200
 * 11   : 1000000
 */

// Table T2-7: LIST OF AVAIL. PINS TO ASSIGN FUNCTION for command "SX"
/* Pin# : Pin Name  : Default
 * 00   : P00   : UART RTS (Avoid to change)
 * 01   : P05   : Null
 * 02   : P17   : UART CTS (Avoid to change)
 * 03   : P31   : Factory Reset
 * 04   : P32   : Null
 * 05   : P33   : UART RX Indication
 * 06   : P34   : Pairing
 * 07   : P37   : Null
 */

// Table T2-8: LIST OF FUNCTIONS TO ASSIGN TO PINS for command "SX"
/* Func#    : Function  : Input/Output
 * 00   : None                      : N/a
 * 01   : UART RTS                  : Output
 * 02   : Battery Low Ind           : Output
 * 03   : RSSI                      : Output
 * 04   : UART CTS                  : Input
 * 05   : Link Drop                 : Input (NMI)
 * 06   : UART RX Ind               : Input (NMI)
 * 07   : Pairing                   : Input (NMI)
 * 08   : Inquiry                   : Input (NMI)
 * 09   : Profile Indicate          : Output (NMI)
 * 0A   : Command/Data mode switch  : Input (NMI)
 * 0B   : Factory Reset             : Input (NMI)
 * 0C   :
 */


/******************************************************
* GET Commands
*******************************************************/
// Get commands are used to retrieve values from the device
// Get commands typically do not have arguments,
// though the single exception does not delineate its argument with a comma.

#define BT_GET_INFO "D"     /* Args: none
                             * This wil retrieve and display basic settings and info.
                             * Includes Address, name, UART settings, security pin, bonding, & remote addr. */

#define BT_GET_ADDR "GB"    /* Args: none
                             * Returns the Bluetooth Address of the device */

#define BT_GET_STAT "GK"    /* Args: none
                             * Returns the current connection status of the device, in the form of three integers
                             * separated by commas.
                             * Digit 1: 0 or 1, 0 meaning no connection, and 1 meaning connected
                             * Digit 2: 0-6, see table below (T2-9)
                             * Digit 3: 0-2, connection type where 0=SPP, 1=iAP, 2=BLE */

#define BT_GET_SET_VAL "G"  /* Args: <char> (NO COMMA DELINEATION)
                             * The argument for this command is NOT separated by a comma, and can be any char from the
                             * list of "SET" commands above. This will return the value set by the corresponding char.
                             * Example: if SQ set value 37, then GQ will return 37. */

// Table T2-9: AUTHENTICATION STATUS for command "GK"
/* Val: Description
 * 0 : No iAP or BLE auth
 * 1 : Successful authentication
 * 2 : APP open; Bluetooth connection over iAP ready
 * 3 : APP closed, no data transfer possible
 * 4 : On power-up, the authentication processor test failed
 * 5 : Authentication attempted and failed
 * 6 : BLE link authenticated
 */

/******************************************************
* ACTION Commands
*******************************************************/
// Action commands perform actions such as inquiry, connecting, entering/exiting command mode
// Action commands typically do NOT have arguments
// Action commands are assumed to be volatile, and reset to defaults when the module is reset

#define BT_ENTER_CMD "$$$"              /* Args: none
                                         * This command causes the device to enter Command Mode and display a command
                                         * prompt. The device passes characters as data until it sees this exact
                                         * sequence. The specific character used can be changed with the command "S$".
                                         * BECAUSE this is not a command, but an escape sequence, it does not require
                                         * a carriage return */

#define BT_EXIT_CMD "---"               /* Args: none
                                         * This command causes the device to exit Command Mode, displaying "END" */

#define BT_TOGGLE_LOCAL_ECHO "+"        /* Args: none
                                         * This command toggles the local echo on and off. If sent in Command Mode, all
                                         * typed characters are echoed to the output afterward. */

#define BT_ASSN_RAND_ADDR "&,"           /* Args: <6ByteAddress>
                                         * BLE ONLY: This command assigns a random address to the local device. It
                                         * accepts one input parameter; a six-byte random address, static or private.
                                         * For the format of a random address, refer to the Bluetooth Bore specification
                                         * version 4.1, Vol 3, Part C, Sec 10.8. If the device is currently advertising,
                                         * the advertising address immediately changes to the assigned random address. */

#define BT_CLEAR_RAND_ADDR "&C"         /* Args: none
                                         * BLE ONLY:
                                         * This clears the random address and uses the local MAC address for
                                         * advertisement. If the device is currently advertising, the advertising
                                         * address immediately changes to the local MAC address. */

#define BT_GEN_RAND_ADDR "&R"           /* Args: none
                                         * BLE ONLY:
                                         * This generates a resolvable random address and assigns it as the current
                                         * random address. This address is output to UART as a response to the command.
                                         * If the device is currently advertising, the advertising address changes
                                         * immediately to this this new resolvable random address. */

#define BT_BOND_DEVICES "B"             /* Args: none
                                         * BLE ONLY:
                                         * Used to secure the connection and bond two connected devices. This is ONLY
                                         * effective if the two devices are already connected. Bonding can be initiated
                                         * by either the central or the peripheral device. Once bonded, security
                                         * materials are saved in both ends of the connection. Therefore, reconnection
                                         * between bonded devices does not require pin code exchange, which reduces
                                         * reconnection time.
                                         * If the bonded connection is lost for any reason, the reconnection does not
                                         * automatically secure the link. To secure the link, another "B" must be
                                         * issued. However, command B is ONLY for securing the link other than saving
                                         * connection information. */

#define BT_CONNECT_TO "C,"               /* This command has multiple different functions depending on the arguments:
                                         * CLASSIC: [<Address>]
                                         *  This initiates a BT classic connection to a device. If no argument is given,
                                         *  then the module attempts to connect to the last connected device. If no
                                         *  prior connection is established, then an error message is returned.
                                         * BLE: <0,1>,<Address>
                                         *  This connects to a remote BLE device with <address>, where <address> is in
                                         *  hexadecimal format. The first parameter specifies the connection type.
                                         *  0 for public addresses, 1 for private random addresses. When this command is
                                         *  used to connect to a device that has already been bonded, the link is NOT
                                         *  automatically secured. Use command B to secure the link after the connection
                                         *  is established.
                                         * BLE: <1-8> NOT separated by a comma, ie C1, C2, ...
                                         *  This command is used to reconnect to a previously connected device that is
                                         *  stored in the saved paired device list, indexed from 1 to 8. To list devices
                                         *  stored, use the command "Y". Reconnection with a BLE device with a random
                                         *  address may NOT be successful, if the target device has changed its address. */

#define BT_BEGIN_INQUIRY "F"            /* Args: [<0-5>[,<hex>]]
                                         * This accepts UP TO two optional arguments. This starts the inquiry process to
                                         * find Bluetooth devices nearby. Default lasts for 20 seconds, configured by
                                         * the command SL.
                                         * The first input parameter specifies the inquiry mode. If not provided, normal
                                         * inquiry is used. Depending on the inquiry mode, a second parameter may be
                                         * necessary. See table T2-11 below for the list of modes and parameters. */

#define BT_ADS_INSTANCE_ADVERT "IA,"     /* Args: <H8>,<Hex>
                                         * This and the following five commands all handle the advertisement (A),
                                         * beacon (B), and scan response (C) payload formats. All advertisement, beacon,
                                         * or scan response data are composed of one or more "Advertisement Structure"
                                         * (AD Structure). Each AD Structure has one byte of length, one byte of
                                         * Advertisement Type (AD Type), and various lengths of Advertisement Data (AD
                                         * Data). The set of commands either appends an AD Structure, or removes all AD
                                         * Structures, depending on the first parameter.
                                         *
                                         * The commands that begin with I make changes effective Immediately, without
                                         * reboot. The changes are not saved into NVM and WILL NOT survive a power
                                         * cycle. This command is suitable to broadcast dynamic data in the AD
                                         * Structure. Commands that begin with N make permanent changes, and require a
                                         * reboot to take effect.
                                         *
                                         * The second letter in the command indicates the type of information to be
                                         * changed; A for Advertisement, B for Beacon, and C for Scan Response.
                                         *
                                         * The first parameter is the AD Type: Bluetooth SIG defines AD Types in the
                                         * Assigned Number List in the Core Specification. If the AD type is set to
                                         * zero, which is NOT defined by the SIG, then ALL AD Structures are cleared.
                                         * Table T2-12 lists the commonly used AD Types
                                         *
                                         * The second parameter is the AD data. AD data has various lengths and follows
                                         * the format defined in Bluetooth SIG Supplement to the Bluetooth Core
                                         * Specification. */

#define BT_ADS_INSTANCE_BEACON "IB,"        /* Args: <H8>,<Hex>
                                             * See Above */

#define BT_ADS_INSTANCE_SCAN_RESPONSE "IC," /* Args: <H8>,<Hex>
                                             * See Above */

#define BT_ADS_PERMANENT_ADVERT "NA,"       /* Args: <H8>,<Hex>
                                             * See Above */

#define BT_ADS_PERMANENT_BEACON "NB,"       /* Args: <H8>,<Hex>
                                             * See Above */

#define BT_ADS_PERMANENT_SCAN_RESPONSE "NC,"/* Args: <H8>,<Hex>
                                             * See Above */

#define BT_WHITELIST_MAC "JA,"          /* Args: <Address> (CLASSIC) or <0,1>,<Address> (LE)
                                         * This adds a MAC address to the whitelist, and simultaneously enables the
                                         * whitelist feature. Up to 16 classic or BLE devices can be added.
                                         * The standard whitelist applies ONLY to BLE, but this module extends it to
                                         * Classic. When enabled in the master role, ONLY devices in the list may will
                                         * be shown inquiry results. When in slave mode, ONLY devices in the white list
                                         * can be connected with the local device.
                                         * This expects one or two input parameters. If only one, it indicates that the
                                         * MAC address is that of a Classic device. If two, the first is a single digit
                                         * that specifies the address type, where 0 is public and 1 is private. The
                                         * second input parameter is the BLE MAC address to be added to the whitelist.
                                         * Random addresses that are added to the list using this method have NO
                                         * resolvable capability, and therefore, once a BLE device with a random address
                                         * changes its address, it is no longer on the whitelist. For resolvable random
                                         * addresses, refer to the command "JB" */

#define BT_WHITELIST_ALL "JB,"          /* Args: none
                                         * This adds all bonded devices, Classic and LE, to the whitelist. If the BLE
                                         * device listed in the whitelist has a resolvable random address, then the
                                         * module has the capability to identify that BLE device even if the RRA has
                                         * changed to another value. */

#define BT_CLEAR_WHITELIST "JC,"        /* Args: none
                                         * This clears the whitelist and simultaneously disables the whitelist feature */

#define BT_DISPLAY_WHITELIST "JD,"      /* Args: none
                                         * This displays all devices on the whitelist. If Classic, only the MAC address
                                         * is shown. BLE devices show both the address and the address type, separated
                                         * by a comma. 0 represents a public address and 1 is a private address */

#define BT_KILL_LINK "K,1"              /* Args: none (self-contained)
                                         * Kill/disconnect the current link */

#define BT_GO_DORMANT "O,0"             /* Args: none (self-contained)
                                         * Put module in Dormant mode, with NO UART RESPONSE. The module enters a Deep
                                         * Sleep state with NO RF communication. Here, the current draw is lowest. If
                                         * the host MCU needs to wake the device up, the MCU must pull the WAKE_UP pin
                                         * low. Upon wakeup, the module starts out of a Reset. */

#define BT_GO_QUIET "Q,"                /* Args: [<0-3> or ?]
                                         * Puts the device into Quiet mode, meaning that it is temporarily NOT
                                         * discoverable or connectable. This does NOT survive a power cycle/reset.
                                         *  With no argument, the module is undiscoverable for Classic and LE
                                         *  0: Discoverable AND connectable for Classic and LE (AOK)
                                         *  1: Undiscoverable AND unable to connect for Classic and LE
                                         *  2: Connectable, but undiscoverable in Classic
                                         *  3: Undiscoverable in LE
                                         *  ?: Displays the current quiet mode */

#define BT_FORCE_REBOOT "R,1"           /* Args: none (self-contained)
                                         * Forces a complete device reboot, similar to a power cycle. */

#define BT_CONFIG_LE "T,"               /* Args: <H16>,<H16>,<H16>,<H16>
                                         * BLE ONLY: Adjusts the connection parameters after establishing the BLE
                                         * connection.
                                         * Parameter 1 is a 16bit hex value for the minimum connection interval with
                                         *  units of 1.25 ms
                                         * Parameter 2 is a 16bit hex value for the maximum connection interval with
                                         *  units of 1.25 ms
                                         * Parameter 3 is slave latency
                                         * Parameter 4 is the supervision timeout with units of 10 ms */

#define BT_REMOVE_DEVICE "U,"           /* Args: <Z> OR <1-8>
                                         * Removes one or more devices from the linked device list. It expects one input
                                         * parameter. The linked device list can be accessed with the command "Y".
                                         * If the input parameter is "Z", then all devices are removed.
                                         * The input parameter can also be a single digit 1 through 8, corresponding to
                                         * any of the eight possible devices in the linked device list. */

#define BT_DISPLAY_FW "V"               /* Args: none
                                         * Displays firmware version */

#define BT_QUIET_LEGACY "W"             /* Args: none
                                         * Has the same effect as command "Q,0". Here for backward compatibility.
                                         * Enables discovery and connection after it has been disabled with command Q.
                                         * It reloads the stored value of the Inquiry and Page Window in Inquiry and
                                         * Page Scan. */

#define BT_TERMINATE_SCAN "X"           /* Args: none
                                         * Terminate a scan operation before the duration expires for both Classic and
                                         * LE. This is one of the few commands that does not have to wait for a command
                                         * prompt. */

#define BT_DISPLAY_STORED_MAC "Y"       /* Args: none
                                         * Displays the MAC addresses of the devices in the stored device list. Format:
                                         * <index>,<priority>,<BT address>[,<LE address type>] */

#define BT_STOP_CONNECTION_ATTEMPT "Z"  /* Args: none
                                         * Stops the current connection attempt before connection is established. Does
                                         * not have to wait for a command prompt. */


// Table T2-11: INQUIRY MODES for command "F"
/* Mode Index : Name : Desc : Expected second parameter
 * 0 : Normal       : Perform normal inquiry; return all bt classic     : None
 *   :              : devices in the neighborhood.                      :
 *   :              :                                                   :
 * 1 : Address      : Inquiry results are filtered with a specific BT   : A 7-byte parameter: 1st is address mask and
 *   :              : address.                                          : the remaining 6 are the BT MAC address. The
 *   :              :                                                   : lower 6 bits of the mask specify if the
 *   :              :                                                   : corresponding byte in the MAC address is
 *   :              :                                                   : effective in filtering. A bit set means that
 *   :              :                                                   : the corresponding address byte is effective.
 *   :              :                                                   :
 * 2 : COD          : Inquiry results filtered with a specified Class   : A 3-byte COD. Only devices with the same COD
 *   :              : of Device (COD)                                   : appear in the scan result.
 *   :              :                                                   :
 * 3 : Device Name  : Inquiry results filtered with ONLY one specified  : Expects the device name as the second
 *   :              : device name.                                      : parameter.
 *   :              :                                                   :
 * 4 : RSSI         : Inquiry scans with RSSI value                     : None
 *   :              :                                                   :
 * 5 : BLE          : BLE scan                                          : Optional: 16-bit input parameters for scan
 *   :              :                                                   : window and scan interval.
 */

// Table T2-12: LIST OF AD TYPES for IA/B/C and NA/B/C commands
/* AD Type : Description
 * 00 : Clear all AD Structure
 * 01 : Flags
 * 02 : Incomplete list of 16bit UUIDs
 * 03 : Complete list of 16bit UUIDs
 * 04 : Incomplete list of 32bit UUIDs
 * 05 : Complete list of 32bit UUIDs
 * 06 : Incomplete list of 128bit UUIDs
 * 07 : Complete list of 128bit UUIDs
 * 08 : Shortened local name
 * 09 : Complete local name
 * 0A : TX power level
 * 0D : Class of device
 * 0E : Simple pairing hash
 * 0F : Simple pairing randomizer
 * 10 : TK value
 * 11 : Security OOB flag
 * 12 : Slave connection interval range
 * 14 : List of 16bit service UUIDs
 * 15 : List of 128bit service UUIDs
 * 16 : Service data
 * FF : Manufacture specific data
 */

#endif //MICROCONTROLLER_LIBRARIES_RN4678_COMMAND_H