# IPC для Windows

```c
handle CreateFile(PCSTR pszFib name,
  DWORD dwDesize dAcess,
  DWORD dwShareMode, PSECURITY_ATTRIBUTES psa,
  DWORD dwFflagsAnd..,
  HANDLE TemplateFile);


HANDLE CreateFileMapping(HANDLE hFile /* CreateFile */,
  PSEQURITY_ATTRIBUTES psa /* PAGE_READONLY */,
  DWORD fdw Protect,
  DWORD dwMaximumSize high /*  */,
  DWORD dwMaximumSize low,
  PCSTR pczName)
```
