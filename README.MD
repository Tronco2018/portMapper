# PortMapper host scanner
This program allowes to scan for open ports on a specific host.
The ports scanned are $1 - 9999$ by default, you can change these values using the parameters _endingPort_ and _startingPort_.

## Usage
portmapper `<hostIp> [endingPort] [startingPort]`

Examples: 
```bash
    portmapper 192.168.1.1
    portmapper 192.168.1.1 9000 10
```