/*
    Copyright (C) 2014  Intel Corporation

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
#ifndef XFSTKDLDRAPI_H
#define XFSTKDLDRAPI_H
#include "xfstk-dldr-api_global.h"
#include <iostream>

/*! \brief device type
  * \brief Intel SOC device type with different PID
 *  \param None
 *  \note None
 */
#define MOORESTOWN          0x1
#define MEDFIELD            0x2
#define CLOVERVIEW          0x3
#define CLOVERVIEWPLUS      0x4
#define MERRIFIELD          0x5
#define MEDFIELD_EMMC_DUMP  0x6
#define HASHVERIFY          0x7
#define MOOREFIELD          0x8
#define BAYTRAIL            0x9
#define CARBONCANYON        0xA
#define XFSTK_MAXDEVICE     0xB
#define XFSTK_NODEVICE      0x666
/*! \brief Log levels for the callback, set the bit to 1 if you want the API to log the message
  * \brief recommend at least to include LOG_STATUS and LOG_PROGRESS
 *  \param None
 *  \note None
 */
#define LOG_ACK         0x0001
#define LOG_UPDATE      0x0002
#define LOG_OPCODE      0x0004
#define LOG_FWUPGRADE   0x0008
#define LOG_OS          0x0010
#define LOG_USB         0x0020
#define LOG_SOCKET      0x0040
#define LOG_SERIAL      0x0080
#define LOG_UTIL        0x0100
#define LOG_DOWNLOADER  0x0200
#define LOG_ENTRY       0x0400
#define LOG_STATUS      0x0800
#define LOG_PROGRESS    0x1000
#define DEBUG_ERROR     0xfffffff1
#define LOG_ALL         0xffffffff
#define MAX_ARGS 32
/*!
    \struct LastError
    \brief The last error happened during download
    \param error_code -- enum error code from above array index
    \param error_message -- error message related to the error code.
*/
struct LastError {
    unsigned long error_code;
    char error_message[128];
};

#define MAX_USBSN_LENGTH 128

/*!
    \struct SoCDevice
    \brief data struct for port mapping API
    \param usbsn -- Intel SOC device usb serial number string
    \param root_hub -- root hub port number that the SOC device is connected to.
        \Param port[5]  -- port number on each level of the hubs after the root hub that SOC device is connected through
*/
struct SoCDevice {
    char usbsn[MAX_USBSN_LENGTH];
    unsigned long root_hub;
    unsigned long port[5];

};

/*!
    \struct SoCDevices
    \brief data struct for port info for all the devices connected to host
    \param number_devices -- Total number of devices detected
    \param soc_device -- An array of port mapping info of the devices detected.
*/
struct SoCDevices {
    int number_devices;
    SoCDevice soc_device[32];
};

#ifdef XFSTK_OS_WIN
typedef struct DevicesCallBack
{
    SoCDevices* device;
    void (*attach)(void* data);
    void (*detach)(void* data);
    void * clientdata;
}DevicesCallBack;
#endif

/*!
    \typedef xfstkstatuspfn
    \brief Represents an optional status callback function that can be provided to xfstk API to obtain status information.
*/
typedef void(*xfstkstatuspfn)(char* status, void *);
/*!
    \class xfstkdldrapi
    \brief This interface enables the development of Intel SoC firmware/operating system provisioning applications.  This API is not re-entrant.

    \brief Below is a diagram illustrating the general host/target configurations that the API can be used in.

    \image html xfstkcmdclientflow.png

REM 
*/
class XFSTKDLDRAPISHARED_EXPORT xfstkdldrapi {
public:
    /*! \brief Constructs a new xfstkdldrapi instance.
     *  \param None
     *  \return a pointer to a physical instance of xfstkdldrapi.
     *  \exception None
     *  \note None
     */
    xfstkdldrapi();
    /*! \brief Distructs a xfstkdldrapi instance.
     *  \param None
     *  \return a pointer to a physical instance of xfstkdldrapi.
     *  \exception None
     *  \note None
     */
    virtual ~xfstkdldrapi();
	
	
    /*! \brief Allows for the retrieval of the IDRQ response from a device
     *  \param buffer is the where the IDRQ response will be stored
     *  \param maxsize is the maximum space allocated for buffer
     *  \return TRUE if operation was a success or else FALSE
     *  \exception none
     *  \note Method currently only works for Merrifield platforms only
     */
    virtual bool idrqresponse(unsigned char *buffer, int maxsize);

    /*! \brief API method to simulate CLI
     *  \param CLI string
     *  \return TRUE if operation was a success or else FALSE
     *  \exception none
     */
    virtual bool downloadcli(const char *cli);

    /*! \brief Allows downloading a fwimage via spi
     *  \param fwfile is the file that is downloaded
     *  \return TRUE if downloads without error
     *  \exception none
     */
    virtual bool downloadfw(char *fwfile);

    /*! \brief Allows for the writing of a device hash or comparing of the hash to a golden hash file
     *  \param hashfile is the file that will be written to, or the golden file that will be compared to
     *  \param write is the value that determines whether to write to file(TRUE) or read from and compare(FALSE)
     *  \return TRUE if matching hashes or else FALSE
     *  \exception none
     *  \note If writing HASH destination file must be present
     */
    virtual bool hashverify(char *hashfile, bool write);

    /*! \brief Set the response buffer for the CSDB provisioning
     *  \param responseBuffer buffer to be used
     *  \param maxsize the maximum size of the buffer
     *  \return none
     *  \exception
     *  \note Call this before running the downloadcsdb() function
     */
    virtual void setcsdbResponsebuffer(unsigned char* responseBuffer, int maxsize);

    /*! \brief Performs single shot firmware and operating system download.
     *  \param fwdnx Firmware download and execute (DnX) module.
     *  \param miscbin CSDB Payload file
     *  \param cmdcode CSDB command code
     *  \param fwimage Firmware binary image.
     *  \param direct command no longer valid
     *  \return True / False status indicating provisioning success / failure.
     *  \exception None
     *  \note It is recommended to use the downloadcli() method for CSDB instead
     */
    virtual bool downloadcsdb(char *fwdnx, char *miscbin, char *cmdcode,char *fwimage, bool direct );
    /*! \brief Performs single shot firmware only download.
     *  \param fwdnx Firmware download and execute (DnX) module.
     *  \param fwimage Firmware binary image.
     *  \param gpflags General purpose flags to control download process.  For firmware only download specify 0x80000000.
     *  \return True / False status indicating provisioning success / failure.
     *  \exception None
     *  \note gpflags can be set to other values.  Please contact your Intel representative for additional details.
     */
    virtual bool downloadfw(char *fwdnx, char *fwimage, char *gpflags);

    /*! \brief Performs single shot operating system only download.
     *  \param osdnx Operating System download and execute (DnX) module.
     *  \param osimage Operating System binary image.
     *  \param gpflags General purpose flags to control download process.  For os only download specify 0x80000001.
     *  \return True / False status indicating provisioning success / failure.
     *  \exception None
     *  \note gpflags can be set to other values.  Please contact your Intel representative for additional details.
     */
    virtual bool downloados(char *osdnx, char *osimage, char *gpflags);

    /*! \brief Performs single shot firmware and operating system download.
     *  \param fwdnx Firmware download and execute (DnX) module.
     *  \param fwimage Firmware binary image.
     *  \param osdnx Operating System download and execute (DnX) module.
     *  \param osimage Operating System binary image.
     *  \param gpflags General purpose flags to control download process.  For firmware & os download specify 0x80000001.
     *  \return True / False status indicating provisioning success / failure.
     *  \exception None
     *  \note gpflags can be set to other values.  Please contact your Intel representative for additional details.
     */
    virtual bool downloadfwos(char *fwdnx, char *fwimage, char *osdnx, char* osimage, char* gpflags);

    /*! \brief Performs single shot firmware and operating system download.
     *  \param fwdnx Firmware download and execute (DnX) module.
     *  \param fwimage Firmware binary image.
     *  \param osdnx Operating System download and execute (DnX) module.
     *  \param osimage Operating System binary image.
     *  \param gpflags General purpose flags to control download process.  For firmware & os download specify 0x80000001.
     *  \param softfuse Softfuse binary image.
     *  \return True / False status indicating provisioning success / failure.
     *  \exception None
     *  \note gpflags can be set to other values.  Please contact your Intel representative for additional details.
     */

    virtual bool downloadfwos(char *fwdnx, char *fwimage, char *osdnx, char* osimage, char* gpflags, char* softfuse);

    /*! \brief Performs parallel multitarget firmware and operating system download in async mode, it will return after the download to the device is done.
     *  \param fwdnx Firmware download and execute (DnX) module.
     *  \param fwimage Firmware binary image.
     *  \param osdnx Operating System download and execute (DnX) module.
     *  \param osimage Operating System binary image.
     *  \param gpflags General purpose flags to control download process.  For firmware & os download specify 0x80000001.
     *  \param usbsn the usb serial number of the device, client need to detect the USB serial number first and provide it to the API.
     *  \return True / False status indicating provisioning success / failure.
     *  \exception None
     *  \note gpflags can be set to other values.  Please contact your Intel representative for additional details.  When programming multiple targets 1 thread will be spawned per target if possible.
     *  \note **** The client app will need to detect the device and use the detected USBSN to start a thread to call this API, prefered method for MFG tools.
     */

    virtual bool downloadmtfwosasync(char *fwdnx, char *fwimage, char *osdnx, char* osimage, char* gpflags, char* usbsn);

    /*! \brief Performs parallel multitarget firmware and operating system download in async mode, it will return after the download to the device is done.
     *  \param fwdnx Firmware download and execute (DnX) module.
     *  \param fwimage Firmware binary image.
     *  \param osdnx Operating System download and execute (DnX) module.
     *  \param osimage Operating System binary image.
     *  \param gpflags General purpose flags to control download process.  For firmware & os download specify 0x80000001.
     *  \param usbsn the usb serial number of the device, client need to detect the USB serial number first and provide it to the API.
     *  \param softfuse Softfuse binary image.
     *  \return True / False status indicating provisioning success / failure.
     *  \exception None
     *  \note gpflags can be set to other values.  Please contact your Intel representative for additional details.  When programming multiple targets 1 thread will be spawned per target if possible.
     *  \note **** The client app will need to detect the device and use the detected USBSN to start a thread to call this API, prefered method for MFG tools.
     */

    virtual bool downloadmtfwosasync(char *fwdnx, char *fwimage, char *osdnx, char* osimage, char* gpflags, char* usbsn, char* softfuse);

    /*! \brief Registers a callback with the xfstk api in order to obtain download status information.
     *  \param statuspfn Pointer to a callback function which has the same signature as xfstkstatuspfn.
     *  \param clientdata Optional pointer to a client data object.  Can be NULL.
     *  \return True / False status indicating registration success / failure.
     *  \exception None
     *  \sa This setting can be used to work around host side USB issues.  Such issues may be caused by faulty usb hubs, usb hub daisy chains, very high host system load, poor quality usb cables, usb enumeration delays within host operating system, etc...
     */
    virtual bool registerstatuscallback(xfstkstatuspfn statuspfn, void *clientdata);

    /*! \brief Sets the number of retries to perform during faulty USB I/O.
     *  \param retries Integer value corresponding to the number of times to retry faulty USB I/O transfers.  Default is 40.
     *  \return None
     *  \exception None
     *  \note This setting can be used to work around host side USB issues.  Such issues may be caused by faulty usb hubs, usb hub daisy chains, very high host system load, poor quality usb cables, usb enumeration delays within host operating system, etc...
     */       
    virtual void settargetretrycount(int retries);

    /*! \brief Sets log level for the API to limit the messages send back to the callback.
     *  \param unsigned long, loglevel
     *  \return None
     *  \exception None
     */
    virtual void setloglevel(unsigned long loglevel);

    /*! \brief Sets the files path for softfuse
     *  \param  type - bool  - include/exclude softfuse.
     *  \param  type - char *   - string path for softfuse file.
     *  \return None
     *  \exception None
     *  \note
     */
    virtual void setsoftfusepath(bool include, char * softfuse);


    /*! \brief Sets the files path for miscdnx, this one is only for advanced feature in TNG USB 3.0 POC.
     *  \param  type - bool  - enable/disable miscdnx.
     *  \param  type - char *   - string path for miscdnx file.
     *  \return None
     *  \exception None
     *  \note
     */
    virtual void setmiscdnxpath(bool enable, char * miscdnx);

    /*! \brief Reports the number of available targets connected to the host system.
     *  \param None
     *  \return Integer value representing the number of conencted targets
     *  \exception None
     *  \note Visibility of targets is dependent on your firmware configuration.  If you are having a problem detecting targets please contact your Intel representative for assistance.
     */
    virtual int getavailabletargets();
    /*! \brief Reports the number of available targets connected to the host system for devicetype.
     *  \param None
     *  \return Integer value representing the number of conencted targets
     *  \exception None
     *  \note Visibility of targets is dependent on your firmware configuration.  If you are having a problem detecting targets please contact your Intel representative for assistance.
     */
    virtual int getavailabletargets(unsigned long devicetype);

    /*! \brief Reports the number of available targets connected to the host system.
     *  \param socdevices An array of the socdevice port mapping data for detected devices
     *  \return Integer value representing the number of conencted targets
     *  \exception None
     *  \note The data from socdevices can be used by Client Apps to display the port info and usbsn based the physical port.
     */
    virtual int getavailabletargets(SoCDevices * socdevices);
#ifdef XFSTK_OS_WIN
    /*! \brief Register callback functions for device attach and detach events.
     *  \param socdevices An array of the socdevice port mapping data for detected devices
     *  \param Optional - Pointer to device attach callback function
     *  \param Optional - Pointer to device detach callback function
     *  \param type Unsigned long - Platform ID as defined above
     *  \return bool - Successfully register true else false
     *  \exception None
     *  \note
     */
    virtual bool registerdevicecallback(DevicesCallBack* callBackStruct, unsigned long ProductId=0);

#endif

    /*! \brief Lock the usb device mutex, only call this before scanning the device for USBSN.
     *  \param None
     *  \return None
     *  \exception None
     *  \note Since libusb driver is not multi thread safe during USB device enumeration, we added this lock for thread safty.
     */
    virtual void usbdevicemutexlock();
    /*! \brief Unlock the usb device mutex, call this after a UBS device is found and before call downloadmtfwosasync().
     *  \param None
     *  \return None
     *  \exception None
     *  \note Client should not hold this lock when call the API downloadmtfwosasync() to start download since this mutex is shared with API
     *  \     It will block the API if it is in lock status before call the API.
     */
    virtual void usbdevicemutexunlock();
    /*! \brief Get the XFSTK API version string.
     *  \param char*, client should allocate memory for this version string, should be at least 8 byte long.
     *  \return None
     *  \exception None
     *  \note
     */
    virtual void getversion(char* version);
    /*! \brief Get the XFSTK API version string.
     *  \param
     *  \return std::string
     *  \exception None
     *  \note
     */
    virtual std::string getfullversion(void) const;

    /*! \brief Get the Last error from XFSTK API version string.
     *  \param LastError*, client should allocate memory for the LastError.
     *  \return true/false
     *  \exception None
     *  \note
     */
    virtual bool getlasterror(LastError* er);
    /*! \brief Set the delay time for before each USB bulk read/write in miliseconds.
     *  \param unsigned long delayms.
     *  \return true/false
     *  \exception None
     *  \note For some hubs or PCI -E USB cards, it may adjust this delay to make it more stable.
     */
    virtual void setusbreadwritedelay(unsigned long delayms);

    /*! \brief Not a POR feature, only a testing/debug feature. 
        \brief Set enable or disable to wipe out ifwi image content before flash the new ifwi,
        \brief If set gpflags = 0x80000000 and set to enable, then it will only wipe out ifwi wout flashing a new one,
        \brief to make the device like a virgin part, but it won't erase OS and user data though.
     *  \param bool - true - enable, false - disable.
     *  \return true/false
     *  \exception None
     *  \note
     */
    virtual void setwipeifwi(bool enable);




private:
    xfstkstatuspfn physstatuspfn;
    void *physclientdata;
    void *xfstkfactoryhandle;
	bool binterfaceavailable;
    bool binterfaceclaimed;
    bool interfaceavailable();
    bool claiminterface();
    void releaseinterface();
    void findusbtargets();
    char* miscdnx;
    bool miscdnxenable;
    char* softfuse;
    bool softfuseinclude;
    int retrycount;
    void xfstklogmessage(char *message, void *clientdata);
    void xfstkmultitargetstatuscallback(char *message, void *clientdata);
    void showversion(void);

	xfstkdldrapi( const xfstkdldrapi& );
	xfstkdldrapi& operator=( const xfstkdldrapi& );
};

extern "C" {
	XFSTKDLDRAPISHARED_EXPORT xfstkdldrapi* xfstkdldrapi_alloc();
	XFSTKDLDRAPISHARED_EXPORT void  xfstkdldrapi_dealloc(xfstkdldrapi* obj);
}
#endif // XFSTKDLDRAPI_H
