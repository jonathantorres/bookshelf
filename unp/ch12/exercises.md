## Chapter 12 - IPv4 and IPv6 Interoperability

#### 12.1

During my testing, the IPv6 FTP client always tries the EPRT command but it falls back to the PORT command if we are running on IPv4.

#### 12.2

During my testing, the IPv6 program was able to start by only enabling the `SO_REUSEADDR` option.
