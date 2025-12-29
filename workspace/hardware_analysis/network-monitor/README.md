# Network
## Mac & Ip
### iproute2: Network configuration (ip, ss)
ip link show # list all network interfaces and their MAC addresses
ip link show dev eth0 # show MAC address of a specific interface
ip link set dev eth0 down # bring the interface down before changing MAC
ip link set dev eth0 address 02:11:22:33:44:55 # set a new MAC address
ip link set dev eth0 up # bring the interface back up
ip link set dev eth0 address random # assign a random locally administered MAC
ip -brief link show dev eth0 # quickly verify the current MAC address

ip -V # Verify installation by checking the ip command version
ip link show # Show all network interfaces and their states
ip address show # Display IP addresses assigned to interfaces
ip route show # Display the routing table
ss -tuln # Show active socket statistics (replacement for netstat)


## DNS
### dnsutils
#### Check the IP address of a domain
nslookup example.com # query DNS to get IP of example.com

#### Query a specific DNS server
nslookup example.com 8.8.8.8 # use 8.8.8.8 as the DNS server

#### Reverse lookup (IP → domain)
nslookup 8.8.8.8 # find the hostname associated with an IP

#### Query a specific record type (A, MX, NS, TXT)
nslookup -type=A example.com # query A record (IPv4)
nslookup -type=AAAA example.com # query AAAA record (IPv6)
nslookup -type=MX example.com # query mail servers
nslookup -type=NS example.com # query authoritative name servers
nslookup -type=TXT example.com # query TXT records (SPF, DKIM, etc.)

#### Interactive mode
nslookup # start interactive mode to query multiple domains
> example.com # query inside interactive mode
> set type=MX # change query type inside interactive mode
> exit # exit interactive mode

#### Check default DNS server
cat /etc/resolv.conf # show which DNS servers the system uses

#### Quick test for any DNS resolution
dig example.com # alternative tool, shows detailed DNS info
dig example.com @8.8.8.8 # query example.com using a specific DNS server


## TCP/UDP
### netcat-openbsd:
nc -h # Verify netcat installation and version
nc -l 8080 # Start a TCP listener on port 8080 # Useful for debugging connections or receiving data
nc example.com 80 # nc neverssl.com 80 # Connect to a remote host and port # Acts as a simple TCP client
echo -e "GET / HTTP/1.1\nHost: example.com\n\n" | nc example.com 80 # Send a simple HTTP request manually
nc -zv 127.0.0.1 20-100 # Scan a range of TCP ports on a host # -z : zero-I/O mode (scan only) # -v : verbose output
nc -l 9000 > received_file.txt # Transfer a file (receiver side)
nc 127.0.0.1 9000 < file_to_send.txt # Transfer a file (sender side)

## Http
### curl:
curl --version # Verify curl installation and version
curl https://example.com # Perform a simple HTTP GET request and print response to stdout
curl -I https://example.com # Fetch only HTTP response headers # -I : head request
curl -O https://example.com/file.tar.gz # Download a file and save it with its original name # -O : write output to a file named as the remote file
curl -o myfile.tar.gz https://example.com/file.tar.gz # Download a file and save it with a custom name # -o : specify output file name
curl -L http://example.com # Follow HTTP redirects automatically # -L : follow redirects
curl -X POST -H "Content-Type: application/json" -d '{"key":"value"}' https://api.example.com/data # Send a POST request with JSON data # -X : specify HTTP method # -H : add HTTP header # -d : request body data
curl -v https://example.com # Test API connectivity and show detailed request/response info # -v : verbose output

### busybox:
busybox --help # Verify BusyBox installation and version
busybox # List all applets (commands) provided by BusyBox
busybox sh # Run a BusyBox shell # Useful in minimal or recovery environments
busybox ls -l / # Use BusyBox ls applet to list directory contents
busybox ps # Use BusyBox ps applet to show running processes
busybox wget http://example.com # Use BusyBox wget applet to fetch a web page
busybox ifconfig # Check network interfaces using BusyBox ifconfig applet

## Files
### wget
wget --version # Verify wget installation and version
wget https://example.com/file.tar.gz # Download a file from a URL and save it locally
wget -O myfile.tar.gz https://example.com/file.tar.gz # Download a file and save it with a custom name # -O : specify output file
wget -c https://example.com/largefile.iso # Resume a partially downloaded file # -c : continue download
wget -q https://example.com/file.tar.gz # Download a file quietly (no output) # -q : quiet mode
wget -r -np -k https://example.com # Mirror a website recursively # -r : recursive # -np : no parent directories # -k : convert links for local viewing

## Ftp
### libcurl
curl-config --version # Verify libcurl version and SSL backend
curl-config --ssl-backends # Verify libcurl version and SSL backend
curl-config --cflags # Show compiler and linker flags required to use libcurl in C/C++ # This is the correct "import" mechanism for libcurl
curl-config --libs # Show compiler and linker flags required to use libcurl in C/C++ # This is the correct "import" mechanism for libcurl
gcc example.c $(curl-config --cflags --libs) -o example # Compile a C program that uses libcurl (example workflow) # gcc example.c $(curl-config --cflags --libs) -o example
./example # Run the compiled program
ldd ./example | grep curl # Check that the libcurl shared library is correctly linked

## Telnet
### telnet
telnet # Verify telnet installation
telnet example.com 23 # Connect to a remote host on the default Telnet port (23)
telnet example.com 80 # Test connectivity to a specific TCP port (common debugging use) # Send a simple HTTP request manually over Telnet # Press Enter twice after typing the request # Exit the telnet session cleanly # Ctrl + ] then type 'quit'

### libtelnet-dev
ls /usr/include/telnet.h # Verify installation by checking header files location
gcc example.c -o example -ltelnet # Compile a C program using libtelnet # -ltelnet links the libtelnet library # example.c is your source file
./example # Run the compiled program
ldd ./example | grep telnet # Check that the compiled program links to libtelnet
ls /usr/share/doc/libtelnet-dev/examples # Optional: explore example programs provided by libtelnet (if installed)

## RSH / RLOGIN
### inetutils-tools
hostname --version, ping -V, ftp --version, telnet --version # Verify installation of key utilities
hostname # Display the system hostname
ping -c 4 example.com # Test network connectivity to a host
ftp ftp.example.com # Connect to a remote host via FTP
telnet example.com 23 # Connect to a remote host via Telnet
host example.com # Resolve a hostname to IP address
host 93.184.216.34 # Reverse lookup of an IP address

## SSH
### openssh-client: SSH client # Debian/Ubuntu # ssh user@host
#### SSH keys: ~/.ssh/
#### Files
####     Private key (keep secret): id_rsa
####     Private key for Ed25519 (newer): id_ed25519
####     Public key (share with server): id_rsa.pub
####     Public key: id_ed25519.pub
#### Then: ssh user@server_ip
ssh -V # Verify ssh installation and version
ssh user@example.com # Connect to a remote server via SSH
scp localfile.txt user@example.com:/remote/path/ # Copy a local file to a remote server using SCP
scp user@example.com:/remote/path/remotefile.txt ./localfile.txt # Copy a file from a remote server to local machine
sftp user@example.com # Transfer files interactively via SFTP
ssh-keygen -t rsa -b 4096 -f ~/.ssh/id_rsa -C "your_email@example.com" # Generate a new SSH key pair (RSA, 4096-bit)
eval "$(ssh-agent -s)" # Add your private key to the SSH agent
ssh-add ~/.ssh/id_rsa # Add your private key to the SSH agent
ssh -i ~/.ssh/id_rsa user@example.com # Test SSH connection using key authentication

### openssh-server: SSH server # Debian/Ubuntu # sudo systemctl enable --now ssh # start & enable
#### Public key: ~/.ssh/authorized_keys
#### Dockerfile
    ## Create SSH run directory (required by sshd)
    #RUN mkdir -p /var/run/sshd
    ## Set root password (for testing/demo purposes; replace in production)
    #RUN echo 'root:rootpassword' | chpasswd
    ## Expose default SSH port
    #EXPOSE 22
sshd -V # Verify sshd installation and version
mkdir -p /var/run/sshd # Create directory required for sshd runtime
/usr/sbin/sshd -D # Start the SSH daemon in the foreground (for containerized use) # -D : do not detach (stay in foreground)
systemctl status ssh # Note: systemctl may not work in containers # Check SSH server status
ssh root@<container-ip> # Test SSH connection from another machine
passwd # Optionally, change root password
useradd -m -s /bin/bash newuser # Add a new user for SSH login
passwd newuser # Add a new user for SSH login

## Ip and Port network scanning
### nmap
nmap --version # Verify nmap installation and version
nmap 192.168.1.0/24 # Scan multiple hosts or a subnet # scan all devices on your local Wi-Fi/LAN, not just your own machine.
nmap -p 20-1024 192.168.1.1 # Scan a specific range of ports on a host
nmap 192.168.1.1 # Scan a single host to detect open TCP ports
nmap -sV 192.168.1.1 # Perform a service and version detection scan
nmap -A 192.168.1.1 # Perform an aggressive scan with OS detection and traceroute
nmap -oN scan_results.txt 192.168.1.1 # Save scan output to a file
nmap -sS -v 192.168.1.1 # Scan using TCP SYN scan (default) with verbose output

## packet capture
### tcpdump
tcpdump --version # Verify tcpdump installation and version
tcpdump -D # List available network interfaces
tcpdump -i eth0 # tcpdump -i wlp1s0 # Capture packets on a specific interface # -i : network interface
tcpdump -n -i eth0 # tcpdump -n -i wlp1s0 # Capture packets with human-readable output # -n : do not resolve hostnames
tcpdump -i eth0 tcp # Capture only TCP traffic
tcpdump -i eth0 port 80 # Capture traffic on a specific port (e.g., HTTP)
tcpdump -i eth0 -w capture.pcap # Capture packets and write them to a file for later analysis # -w : write to pcap file
tcpdump -r capture.pcap # Read packets from a previously captured file # -r : read from pcap file
tcpdump -i eth0 -c 50 # Capture a limited number of packets and then stop # -c : packet count

## Manage networks
### iw, wpa_supplicant, dhclient
sudo iw dev wlp1s0 scan | grep SSID # Scan Wi-Fi networks
sudo iw dev wlan0 connect "SSID_NAME" # Connect
sudo ip link set wlan0 up # Connect
sudo wpa_passphrase "SSID_NAME" "PASSWORD" > /etc/wpa_supplicant.conf # Connect to a network
sudo wpa_supplicant -B -i wlan0 -c /etc/wpa_supplicant.conf # Connect to a network
sudo dhclient wlan0 # Get IP
sudo wpa_supplicant -B -i wlan0 -c /etc/wpa_supplicant.conf # Create a config for multiple networks. Then start.
sudo dhclient wlan0 # Create a config for multiple networks. Then start.

## Bluetooth
### bluez: Classic Bluetooth scan
hcitool -h # Verify hcitool installation
hcitool dev # List available Bluetooth adapters
hcitool scan # Scan for nearby Bluetooth devices
hcitool info 6C:1E:90:03:34:11 # Get information about a specific Bluetooth device # Replace XX:XX:XX:XX:XX:XX with the device address
hcitool inq # Perform a low-level inquiry to detect Bluetooth devices
hcitool con # Check the connection status of a Bluetooth device

hciconfig -h # Verify hciconfig installation
hciconfig # List all Bluetooth interfaces and their status
hciconfig hci0 up # Enable a Bluetooth interface # Replace hci0 with your interface name
hciconfig hci0 down # Disable a Bluetooth interface
hciconfig hci0 reset # Reset a Bluetooth interface
hciconfig hci0 # Display detailed information about a Bluetooth interface
hciconfig hci0 piscan # Set a device to be discoverable
hciconfig hci0 noscan # Set a device to be non-discoverable

btmon -h # Verify btmon installation and display help
btmgmt info # List available Bluetooth controllers
sudo btmon # Start monitoring all Bluetooth HCI traffic # Root privileges are required
sudo btmon -i hci0 # Monitor traffic from a specific Bluetooth interface # Replace hci0 with the desired interface
sudo btmon -w btmon_capture.log # Save captured Bluetooth traffic to a log file # -w : write output to file
btmon -r btmon_capture.log # Read and display a previously saved btmon capture file # -r : read from file
sudo btmon -i hci0 -w btmon_live.log # Combine live monitoring with file capture

lescan --help # Verify lescan tool availability
sudo lescan # Perform a Bluetooth Low Energy (BLE) device scan # Requires root privileges
sudo timeout 10s lescan # Scan for a limited time using timeout (e.g., 10 seconds)
sudo lescan --duplicates # Scan and list only unique devices (avoid duplicate entries)
sudo lescan --duplicates --passive # Combine scanning with verbose output for more details

### bluetoothctl: Interactive CLI
bluetoothctl -v # Verify bluetoothctl installation and version
bluetoothctl # Start interactive bluetoothctl session
list # Inside bluetoothctl, list all available controllers # Command inside interactive shell:
power on # Turn on a Bluetooth controller # Command inside interactive shell:
discoverable on # Make the device discoverable by other Bluetooth devices # Command inside interactive shell:
scan on # Scan for nearby Bluetooth devices # Command inside interactive shell:
pair XX:XX:XX:XX:XX:XX # Pair with a discovered Bluetooth device # Command inside interactive shell:
connect XX:XX:XX:XX:XX:XX # Connect to a paired Bluetooth device # Command inside interactive shell:
trust XX:XX:XX:XX:XX:XX # Trust a paired device to allow automatic connections # Command inside interactive shell:
exit # Exit the bluetoothctl interactive session # Command inside interactive shell:

###
SPP
BLE



### ->
bluetoothctl # start bluetoothctl interactive shell
power on # turn on the bluetooth adapter
scan on # start scanning for nearby devices
# wait and note the MAC address of your device here
pair XX:XX:XX:XX:XX:XX  # pair with the device using its MAC address
trust XX:XX:XX:XX:XX:XX  # trust the device for future connections
connect XX:XX:XX:XX:XX:XX  # connect to the device
# if classic bluetooth SPP device
sudo rfcomm connect /dev/rfcomm0 XX:XX:XX:XX:XX:XX  # create serial connection
cat /dev/rfcomm0  # read data from the serial port
echo "your message" > /dev/rfcomm0  # send data to the device
# if BLE device
gatttool -b XX:XX:XX:XX:XX:XX -I  # start gatttool interactive session
connect  # connect to BLE device inside gatttool
char-read-uuid 2a37  # read characteristic UUID (example)
char-write-req <uuid> <value>  # write value to characteristic
scan off  # stop scanning









# 1. Scan for classic Bluetooth devices
hcitool scan  # lists nearby devices with MAC addresses

# 2. Scan for BLE devices
hcitool lescan  # lists BLE devices (press Ctrl+C to stop)

# 3. Connect to a classic Bluetooth SPP device
sudo rfcomm connect /dev/rfcomm0 6C:1E:90:03:34:11  # replace with device MAC # sudo rfcomm connect /dev/rfcomm0 6C:1E:90:03:34:11 only works for Classic Bluetooth devices that support the Serial Port Profile (SPP).

# 4. Read data from the SPP device
cat /dev/rfcomm0

# 5. Send data to the SPP device
echo "Hello" > /dev/rfcomm0

# 6. Connect to a BLE device using gatttool
gatttool -b XX:XX:XX:XX:XX:XX -I  # replace with device MAC
connect  # inside gatttool prompt

# 7. Read a characteristic from the BLE device
char-read-uuid 2a37  # example UUID

# 8. Write a characteristic to the BLE device
char-write-req <uuid> <value>  # replace with actual UUID and value









#
What you can do instead for BLE

Scan BLE devices
    hcitool lescan  # lists nearby BLE devices

Connect and read data: Use gatttool (deprecated but works) or a Python library like bluepy:
    gatttool -b 19:82:17:4F:60:93 -I  # start interactive BLE session
    connect  # connect to the device
    char-read-uuid 2a37  # read a characteristic (example UUID)


Each BLE device exposes services and characteristics instead of a serial port. You need the correct UUID for the data you want to read.




