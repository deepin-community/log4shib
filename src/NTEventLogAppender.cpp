/*
 * NTEventLogAppender.cpp
 */

#ifdef WIN32	// only available on Win32

#include <log4shib/NTEventLogAppender.hh>

namespace log4shib {

    NTEventLogAppender::NTEventLogAppender(const std::string& name, const std::string& sourceName) :
    LayoutAppender(name),
    _strSourceName(sourceName),
    _hEventSource(NULL)
    {
        open();
    }

    NTEventLogAppender::~NTEventLogAppender()
    {
        close();
    }

    void NTEventLogAppender::open()
    {
        // This has to be done as Admin and should really be app-specific and
        // handled as part of installation or by a deployer.
        //addRegistryInfo(_strSourceName.c_str());
        _hEventSource = ::RegisterEventSource(NULL, _strSourceName.c_str());
    }

    void NTEventLogAppender::close()
    {
        if (_hEventSource) {
            ::DeregisterEventSource(_hEventSource);
        }
    }

    bool NTEventLogAppender::reopen() {
        close();
        open();
        return true;
    }      

    void NTEventLogAppender::_append(const LoggingEvent& event) {
        std::string message(_getLayout().format(event));

        const char* ps[1];
        ps[0] = message.c_str();

        ::ReportEvent(_hEventSource, getType(event.priority), 
	          getCategory(event.priority), 
              0x00001000L, NULL, 1, 0, ps, NULL);
    }

    /**
     * Convert log4shib Priority to an EventLog category. Each category is
     * backed by a message resource so that proper category names will
     * be displayed in the NT Event Viewer.
     */
    WORD NTEventLogAppender::getCategory(Priority::Value priority) {
        // Priority values map directly to EventLog category values
        return (WORD)((priority / 100) + 1);
    }

    /**
     * Convert log4shib Priority to an EventLog type. The log4shib package
     * supports 8 defined priorites, but the NT EventLog only knows
     * 3 event types of interest to us: ERROR, WARNING, and INFO.
     */
    WORD NTEventLogAppender::getType(Priority::Value priority) {

        WORD ret_val;
  
        switch (priority) {
        case Priority::EMERG:
          // FATAL is the same value as EMERG
//        case Priority::FATAL:
        case Priority::ALERT:
        case Priority::CRIT:
        case Priority::ERROR:
            ret_val = EVENTLOG_ERROR_TYPE;
            break;
        case Priority::WARN:
            ret_val = EVENTLOG_WARNING_TYPE;
            break;
        case Priority::NOTICE:
        case Priority::INFO:
        case Priority::DEBUG:
        default:
            ret_val = EVENTLOG_INFORMATION_TYPE;
            break;
        }
        return ret_val;
    }

    HKEY NTEventLogAppender::regGetKey(TCHAR *subkey, DWORD *disposition) {
        HKEY hkey = 0;
        RegCreateKeyEx(HKEY_LOCAL_MACHINE, subkey, 0, NULL, 
            REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, NULL, 
            &hkey, disposition);
        return hkey;
    }

    void NTEventLogAppender::regSetString(HKEY hkey, const TCHAR *name, const TCHAR *value) {
        RegSetValueEx(hkey, name, 0, REG_SZ, (LPBYTE)value, lstrlen(value));
    }

    void NTEventLogAppender::regSetDword(HKEY hkey, const TCHAR *name, DWORD value) {
        RegSetValueEx(hkey, name, 0, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
    }

    /*
     * Add this source with appropriate configuration keys to the registry.
     */
    void NTEventLogAppender::addRegistryInfo(const char *source) {
        static const TCHAR *prefix = "SYSTEM\\CurrentControlSet\\Services\\EventLog\\Application\\";

        TCHAR* subkey = new TCHAR[lstrlen(prefix) + lstrlen(source) + 1];
        lstrcpy(subkey, prefix);
        lstrcat(subkey, source);
        DWORD disposition;
        HKEY hkey = regGetKey(subkey, &disposition);
        delete[] subkey;

        if (disposition == REG_CREATED_NEW_KEY) {
            regSetString(hkey, "EventMessageFile", "NTEventLogAppender.dll");
            regSetString(hkey, "CategoryMessageFile", "NTEventLogAppender.dll");
            regSetDword(hkey, "TypesSupported", (DWORD)7);
            regSetDword(hkey, "CategoryCount", (DWORD)8);
        }
        RegCloseKey(hkey);
        return;
    }

}

#endif // WIN32
