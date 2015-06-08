// fstring.cpp
// class FString

#include "fstring.h"

//----------------------------------------------------------------------
// class FString
//----------------------------------------------------------------------


// constructors and destructor
//----------------------------------------------------------------------
FString::FString()
{
  length  = 0;
  bufsize = 0;
  string  = 0;
  c_string = 0;
}

//----------------------------------------------------------------------
FString::FString (int len)
{
  if ( len >= 0 )
    initLength(uInt(len));
  else
    initLength(0);
}

//----------------------------------------------------------------------
FString::FString (uInt len)
{
  initLength(len);
}

//----------------------------------------------------------------------
FString::FString (int len, wchar_t c)
{
  string  = 0;
  length  = 0;
  bufsize = 0;
  c_string = 0;

  if ( len >= 0 )
    _replace ( FString(uInt(len), c).string );
  else
    initLength(0);
}

//----------------------------------------------------------------------
FString::FString (uInt len, wchar_t c)
{
  register wchar_t* ps;
  register wchar_t* pe;

  initLength(len);
  ps = string;
  pe = string + len;

  while ( pe != ps )
    *--pe = c;
}

//----------------------------------------------------------------------
FString::FString (int len, char c)
{
  string  = 0;
  length  = 0;
  bufsize = 0;
  c_string = 0;

  if ( len >= 0 )
    _replace ( FString(uInt(len), c).string );
  else
    initLength(0);
}

//----------------------------------------------------------------------
FString::FString (uInt len, char c)
{
  register wchar_t* ps;
  register wchar_t* pe;

  initLength(len);
  ps = string;
  pe = string + len;

  while ( pe != ps )
    *--pe = wchar_t(c);
}

//----------------------------------------------------------------------
FString::FString (const FString& s)
{
  string  = 0;
  length  = 0;
  bufsize = 0;
  c_string = 0;
  if ( s.string )
    _replace (s.string);
}

//----------------------------------------------------------------------
FString::FString (const std::wstring& s)
{
  string = 0;
  length  = 0;
  bufsize = 0;
  c_string = 0;
  if ( ! s.empty() )
    _replace ( s.c_str() );
}

//----------------------------------------------------------------------
FString::FString (const wchar_t* s)
{
  string = 0;
  length  = 0;
  bufsize = 0;
  c_string = 0;
  if ( s )
    _replace (s);
}

//----------------------------------------------------------------------
FString::FString (const std::string& s)
{
  string = 0;
  length  = 0;
  bufsize = 0;
  c_string = 0;

  if ( ! s.empty() )
  {
    const wchar_t* wc_str;
    wc_str = c_to_wc_str(s.c_str());

    if ( wc_str )
    {
      _replace( wc_str );
      if ( *wc_str )
        delete[] wc_str;
    }
  }
}

//----------------------------------------------------------------------
FString::FString (const char* s)
{
  const wchar_t* wc_str;

  string = 0;
  length  = 0;
  bufsize = 0;
  c_string = 0;

  wc_str = c_to_wc_str(s);

  if ( wc_str )
  {
    _replace( wc_str );
    if ( *wc_str )
      delete[] wc_str;
  }
}

//----------------------------------------------------------------------
FString::FString (const wchar_t c)
{
  string = 0;
  c_string = 0;
  wchar_t s[2];
  s[0] = c;
  s[1] = L'\0';
  _replace (s);
}

//----------------------------------------------------------------------
FString::FString (const char c)
{
  string = 0;
  c_string = 0;
  wchar_t s[2];
  s[0] = wchar_t(c & 0xff);
  s[1] = L'\0';
  _replace (s);
}

//----------------------------------------------------------------------
FString::~FString()  // destructor
{
  if ( string )
    delete[](string);
  if ( c_string )
    delete[](c_string);
}


// private methods of FString
//----------------------------------------------------------------------
inline void FString::initLength (uInt len)
{
  if ( len > 0 )
  {
    length  = len;
    bufsize = FWDBUFFER + len + 1;
    string  = new wchar_t[bufsize];
    wmemset(string, L'\0', bufsize);
  }
  else
  {
    length  = 0;
    bufsize = 0;
    string = 0;
  }
  c_string = 0;
}

//----------------------------------------------------------------------
inline void FString::_replace (const wchar_t* s)
{
  if ( string )
    delete[](string);

  length =  uInt(wcslen(s));
  bufsize = FWDBUFFER + length + 1;

  try
  {
    string = new wchar_t[bufsize];
  }
  catch (const std::bad_alloc& ex)
  {
    std::cerr << bad_alloc_str << ex.what() << std::endl;
    return;
  }
/*  catch (std::exception& e)
  {
    std::cerr << "not enough memory for a new FString object "
              << e.what() << std::endl;
    return;
  }*/
  wcscpy (string, s);
}

//----------------------------------------------------------------------
inline void FString::_insert (uInt pos, uInt len, const wchar_t* s)
{
  if ( ! string )
  {
    // string is null
    length = len;
    bufsize = FWDBUFFER + length + 1;
    try
    {
      string = new wchar_t[bufsize];
    }
    catch (const std::bad_alloc& ex)
    {
      std::cerr << bad_alloc_str << " " << ex.what() << std::endl;
      return;
    }
    wcscpy (string, s);
    return;
  }
  else
  {
    uInt x;

    if ( (length + len + 1) <= bufsize )
    {
      // output string <= bufsize
      for (x = length+1; x >= pos+1; x--)
        string[x+len-1] = string[x-1];
      for (x=0; x < len; x++)
        string[x+pos] = s[x];
      length += len;
    }
    else
    {
      wchar_t* sptr;
      // output string > bufsize
      bufsize = FWDBUFFER + length + len + 1;

      try
      {
        sptr = new wchar_t[bufsize];
      }
      catch (const std::bad_alloc& ex)
      {
        std::cerr << bad_alloc_str << " " << ex.what() << std::endl;
        return;
      }
      uInt y = 0;
      for (x=0; x < pos; x++)
      sptr[y++] = string[x];
      for (x=0; x < len; x++)
        sptr[y++] = s[x];
      for (x=pos; x <= length; x++)
        sptr[y++] = string[x];
      length += len;
      delete[](string);
      string = sptr;
    }
  }
}

//----------------------------------------------------------------------
inline void FString::_remove (uInt pos, uInt len)
{
  if ( (bufsize - length - 1 + len) <= FWDBUFFER )
  {
    for (uInt i=pos; (i+len) <= length; i++)
      string[i] = string[i+len];
    length -= len;
  }
  else
  {
    wchar_t* sptr;
    bufsize = length + 1 - len + FWDBUFFER;

    try
    {
      sptr = new wchar_t[bufsize];
    }
    catch (const std::bad_alloc& ex)
    {
      std::cerr << bad_alloc_str << " " << ex.what() << std::endl;
      return;
    }
    uInt x, y = 0;
    for (x=0; x < pos; x++)
      sptr[y++] = string[x];
    for (x=pos+len; x <= length; x++)
      sptr[y++] = string[x];
    delete[](string);
    string = sptr;
    length -= len;
  }
}

//----------------------------------------------------------------------
inline char* FString::wc_to_c_str (const wchar_t* s) const
{
  int mblength, size, dest_size;
  const wchar_t* src;

  if ( ! s )  // handle NULL string
    return 0;
  if ( ! *s )  // handle empty string
    return const_cast<char*>("");
  if ( c_string )
    delete[](c_string);

  size = int(wcslen(s)) + 1;
  dest_size = size * int(CHAR_SIZE);
  src = s;
  mbstate_t state;
  memset (&state, '\0', sizeof(mbstate_t));

  try
  {
    c_string = new char[dest_size];

    // pre-initialiaze the whole string with '\0'
    memset (c_string, '\0', size_t(dest_size));
  }
  catch (const std::bad_alloc& ex)
  {
    std::cerr << bad_alloc_str << " " << ex.what() << std::endl;
    return 0;
  }

  mblength = int(wcsrtombs (c_string, &src, uLong(dest_size), &state));

  if ( mblength == -1 && errno != EILSEQ )
  {
    delete[](c_string);
    c_string = 0;
    return const_cast<char*>("");
  }
  return c_string;
}

//----------------------------------------------------------------------
inline wchar_t* FString::c_to_wc_str (const char* s) const
{
  int wclength, size, dest_size;
  const char* src;
  wchar_t* dest;

  if ( ! s )  // handle NULL string
    return 0;
  if ( ! *s )  // handle empty string
    return const_cast<wchar_t*>(L"");


  size = int(strlen(s)) + 1;
  dest_size = size * int(CHAR_SIZE);
  src = s;
  mbstate_t state;
  memset (&state, '\0', sizeof(mbstate_t));

  try
  {
    dest = new wchar_t[size];
    // pre-initialiaze the whole string with '\0'
    wmemset (dest, L'\0', size_t(size));
  }
  catch (const std::bad_alloc& ex)
  {
    std::cerr << bad_alloc_str << " " << ex.what() << std::endl;
    return 0;
  }

  wclength = int(mbsrtowcs (dest, &src, uLong(dest_size), &state));

  if ( wclength == -1 )
  {
    if ( src != s )
      return dest;
    else
    {
      delete[] dest;
      return 0;
    }
  }
  if ( wclength == size )
    dest[size-1] = '\0';
  if ( wclength )
    return dest;
  else
  {
    delete[] dest;
    return 0;
  }
}

//----------------------------------------------------------------------
inline wchar_t* FString::extractToken ( wchar_t** rest,
                                        const wchar_t* s,
                                        const wchar_t* delim )
{
  register wchar_t* token;
  token = ( s ) ? const_cast<wchar_t*>(s) : *rest;

  if ( ! *token )
    return 0;

  *rest = wcspbrk(token, delim);

  if ( *rest )
    *(*rest)++ = '\0';
  else
    *rest = token + wcslen(token);
  return token;
}


// FString operators
//----------------------------------------------------------------------
std::ostream& operator << (std::ostream& outstr, const FString& s)
{
  if ( s.length )
    outstr << s.wc_to_c_str( s.string );
  return (outstr);
}

//----------------------------------------------------------------------
std::istream& operator >> (std::istream& instr, FString& s)
{
  const wchar_t* wc_str;
  char buf[INPBUFFER+1];

  instr.getline (buf, INPBUFFER);
  wc_str = s.c_to_wc_str(buf);

  if ( wc_str )
  {
    s._replace (wc_str);
    if ( *wc_str )
      delete[] wc_str;
  }
  return (instr);
}

//----------------------------------------------------------------------
std::wostream& operator << (std::wostream& outstr, const FString& s)
{
  if ( s.length )
    outstr << s.string;
  return (outstr);
}

//----------------------------------------------------------------------
std::wistream& operator >> (std::wistream& instr, FString& s)
{
  wchar_t buf[INPBUFFER+1];
  instr.getline (buf, INPBUFFER);
  s._replace (buf);
  return (instr);
}

//----------------------------------------------------------------------
FString& FString::operator = (const FString& s)
{
  if ( s )
    _replace (s.string);
  else
    length = bufsize = 0, string = 0;
  return (*this);
}

//----------------------------------------------------------------------
FString& FString::operator = (const std::wstring& s)
{
  if ( ! s.empty() )
    _replace (s.c_str());
  else
    length = bufsize = 0, string = 0;
  return (*this);
}

//----------------------------------------------------------------------
const FString& FString::operator = (const wchar_t* s)
{
  if ( s )
    _replace (s);
  else
    length = bufsize = 0, string = 0;
  return (*this);
}

//----------------------------------------------------------------------
FString& FString::operator = (const std::string& s)
{
  const wchar_t* wc_str = c_to_wc_str(s.c_str());
  if ( wc_str )
  {
    _replace( wc_str );
    if ( *wc_str )
      delete[] wc_str;
  }
  else
    length = bufsize = 0, string = 0;
  return (*this);
}

//----------------------------------------------------------------------
const FString& FString::operator = (const char* s)
{
  const wchar_t* wc_str = c_to_wc_str(s);
  if ( wc_str )
  {
    _replace( wc_str );
    if ( *wc_str )
      delete[] wc_str;
  }
  else
    length = bufsize = 0, string = 0;
  return (*this);
}

//----------------------------------------------------------------------
const FString& FString::operator = (const wchar_t c)
{
  wchar_t s[2];
  s[0] = c;
  s[1] = L'\0';
  _replace (s);
  return (*this);
}

//----------------------------------------------------------------------
const FString& FString::operator = (const char c)
{
  wchar_t s[2];
  s[0] = wchar_t(c & 0xff);
  s[1] = L'\0';
  _replace (s);
  return (*this);
}

//----------------------------------------------------------------------
const FString& FString::operator += (const FString& s)
{
  _insert (length, s.length, s.string);
  return (*this);
}

//----------------------------------------------------------------------
const FString& FString::operator += (const std::wstring& s)
{
  _insert (length, uInt(s.length()), s.c_str());
  return (*this);
}

//----------------------------------------------------------------------
const FString& FString::operator += (const wchar_t* s)
{
  _insert (length, uInt(wcslen(s)), s);
  return (*this);
}

//----------------------------------------------------------------------
const FString& FString::operator += (const std::string& s)
{
  const wchar_t* wc_str = c_to_wc_str(s.c_str());
  if ( wc_str )
  {
    _insert (length, uInt(s.length()), wc_str);
    if ( *wc_str )
      delete[] wc_str;
  }
  return (*this);
}

//----------------------------------------------------------------------
const FString& FString::operator += (const char* s)
{
  const wchar_t* wc_str = c_to_wc_str(s);
  if ( wc_str )
  {
    _insert (length, uInt(strlen(s)), wc_str);
    if ( *wc_str )
      delete[] wc_str;
  }
  return (*this);
}

//----------------------------------------------------------------------
const FString& FString::operator += (const wchar_t c)
{
  _insert (length, 1, &c);
  return (*this);
}

//----------------------------------------------------------------------
const FString& FString::operator += (const char c)
{
  const wchar_t wc = static_cast<wchar_t>(c);
  _insert (length, 1, &wc );
  return (*this);
}

//----------------------------------------------------------------------
const FString FString::operator + (const FString& s)
{
  FString tmp(string);
  tmp._insert (length, s.length, s.string);
  return (tmp);
}

//----------------------------------------------------------------------
const FString FString::operator + (const std::wstring& s)
{
  FString tmp(string);
  tmp._insert (length, uInt(s.length()), s.c_str());
  return (tmp);
}

//----------------------------------------------------------------------
const FString FString::operator + (const wchar_t* s)
{
  FString tmp(string);
  tmp._insert (length, uInt(wcslen(s)), s);
  return (tmp);
}

//----------------------------------------------------------------------
const FString FString::operator + (const std::string& s)
{
  FString tmp(string);
  wchar_t* wc_str = c_to_wc_str(s.c_str());
  if ( ! wc_str )
    return (tmp);
  tmp._insert (length, uInt(wcslen(wc_str)), wc_str);
  if ( *wc_str )
    delete[] wc_str;
  return (tmp);
}

//----------------------------------------------------------------------
const FString FString::operator + (const char* s)
{
  FString tmp(string);
  wchar_t* wc_str = c_to_wc_str(s);
  if ( ! wc_str )
    return (tmp);
  tmp._insert (length, uInt(wcslen(wc_str)), wc_str);
  if ( *wc_str )
    delete[] wc_str;
  return (tmp);
}

//----------------------------------------------------------------------
const FString FString::operator + (const wchar_t c)
{
  FString tmp(string);
  tmp._insert (length, 1, &c);
  return(tmp);
}

//----------------------------------------------------------------------
const FString FString::operator + (const char c)
{
  const wchar_t wc = static_cast<wchar_t>(c);
  FString tmp(string);
  tmp._insert (length, 1, &wc);
  return(tmp);
}

//----------------------------------------------------------------------
const FString operator + (const FString& s1, const FString& s2)
{
  FString tmp(s1);
  tmp._insert ( uInt(wcslen(s1.wc_str())),
                uInt(wcslen(s2.wc_str())),
                s2.wc_str() );
  return (tmp);
}

//----------------------------------------------------------------------
const FString operator + (const std::wstring& s1, const FString& s2)
{
  FString tmp(s1);
  tmp._insert ( uInt(wcslen(s1.c_str())),
                uInt(wcslen(s2.wc_str())),
                s2.wc_str() );
  return (tmp);
}

//----------------------------------------------------------------------
const FString operator + (const wchar_t* s1, const FString& s2)
{
  FString tmp(s1);
  tmp._insert ( uInt(wcslen(s1)),
                uInt(wcslen(s2.wc_str())),
                s2.wc_str() );
  return (tmp);
}

//----------------------------------------------------------------------
const FString operator + (const std::string& s1, const FString& s2)
{
  FString tmp(s1);
  tmp._insert ( tmp.getLength(),
                uInt(wcslen(s2.wc_str())),
                s2.wc_str() );
  return (tmp);
}

//----------------------------------------------------------------------
const FString operator + (const char* s1, const FString& s2)
{
  FString tmp(s1);
  tmp._insert ( tmp.getLength(),
                uInt(wcslen(s2.wc_str())),
                s2.wc_str() );
  return (tmp);
}

//----------------------------------------------------------------------
const FString operator + (const wchar_t c, const FString& s)
{
  FString tmp(c);
  tmp._insert (1, uInt(wcslen(s.wc_str())), s.wc_str());
  return (tmp);
}

//----------------------------------------------------------------------
const FString operator + (const char c, const FString& s)
{
  FString tmp(c);
  tmp._insert (1, uInt(wcslen(s.wc_str())), s.wc_str());
  return (tmp);
}

//----------------------------------------------------------------------
wchar_t& FString::operator [] (uInt pos)
{
  assert ( (pos < length) && "Invalid index position!" );
  if (pos >= length)
    throw std::out_of_range("");
  return (string[pos]);
}

//----------------------------------------------------------------------
const FString FString::operator () (uInt pos, uInt len)
{
  assert ( (pos < length) && ((pos+len) <= length) );
  FString tmp(L"");
  tmp._insert (0, len, string + pos);
  return (tmp);
}


// public methods of FString
//----------------------------------------------------------------------
uInt FString::getUTF8length() const
{
  uInt len;
  const char* s;

  len = 0;
  s = c_str();

  while ( *s )
    len += uInt((*s++ & 0xc0) != 0x80);

  return len;
}

//----------------------------------------------------------------------
FString& FString::sprintf (const wchar_t* format, ...)
{
  const int buf_size = 4096;
  wchar_t buffer[buf_size];
  va_list args;

  va_start (args, format);
  vswprintf (buffer, buf_size, format, args);
  va_end (args);

  this->_replace (buffer);
  return (*this);
}

//----------------------------------------------------------------------
FString& FString::sprintf (const char* format, ...)
{
  const wchar_t* wc_str;
  char  buf[1024];
  char* buffer;
  int   len;
  va_list args;

  buffer = buf;
  va_start (args, format);
  len = vsnprintf (buffer, sizeof(buf), format, args);
  va_end (args);

  if ( len >= int(sizeof(buf)) )
  {
    buffer = new char[len+1];
    va_start (args, format);
    vsnprintf (buffer, uLong(len+1), format, args);
    va_end (args);
  }

  wc_str = c_to_wc_str(buffer);
  if ( wc_str )
  {
    this->_replace(wc_str);
    if ( *wc_str )
      delete[] wc_str;
  }
  if ( buffer != buf )
    delete[] buffer;

  return (*this);
}

//----------------------------------------------------------------------
FString FString::clear()
{
  if ( string )
    delete[](string);
  length  = 0;
  bufsize = 0;
  string  = 0;

  return (*this);
}

//----------------------------------------------------------------------
const wchar_t* FString::wc_str() const
{
  return (string);
}

//----------------------------------------------------------------------
const char* FString::c_str() const
{
  return wc_to_c_str (string);
}

//----------------------------------------------------------------------
const std::string FString::toString() const
{
  return std::string(this->c_str(), length+1);
}

//----------------------------------------------------------------------
FString FString::toLower() const
{
  register wchar_t* p;
  FString s(this->string);
  p = s.string;

  if ( p )
  {
    while ( *p )
    {
      *p = wchar_t(towlower(uInt(*p)));
      p++;
    }
  }
  return s;
}

//----------------------------------------------------------------------
FString FString::toUpper() const
{
  register wchar_t* p;
  FString s(this->string);
  p = s.string;

  if ( p )
  {
    while ( *p )
    {
      *p = wchar_t(towupper(uInt(*p)));
      p++;
    }
  }
  return s;
}

//----------------------------------------------------------------------
long FString::toLong() const
{
  register long num;
  register long tenth_limit;
  register long tenth_limit_digit;
  register wchar_t* p;
  FString s;

  num = 0;
  tenth_limit = LONG_MAX / 10;
  tenth_limit_digit = LONG_MAX % 10;
  s = this->trim();
  p = s.string;

  if ( p )
  {
    register bool neg = false;
    register bool overflow = false;
    if ( *p == '-' )
    {
      p++;
      neg = true;
      tenth_limit = -(LONG_MIN / 10);
      tenth_limit_digit += 1;
    }
    else if ( *p == '+' )
    {
      p++;
    }
    while ( isdigit(*p) )
    {
      register uChar d = uChar((*p) - '0');
      if (  num > tenth_limit
         || (num == tenth_limit && d > tenth_limit_digit) )
      {
        overflow = true;
        break;
      }
      num = (num<<3)+(num<<1) + d;  // (10 * num) + d
      p++;
    }
    if ( overflow )
      num = neg ? LONG_MIN : LONG_MAX;
    else if ( neg )
      num = (~num) + 1;
  }
  return num;
}

//----------------------------------------------------------------------
uLong FString::toULong() const
{
  register uLong num;
  register uLong tenth_limit;
  register uLong tenth_limit_digit;
  register wchar_t* p;
  FString s;

  num = 0;
  tenth_limit = ULONG_MAX / 10;
  tenth_limit_digit = ULONG_MAX % 10;
  s = this->trim();
  p = s.string;

  if ( p )
  {
    register bool overflow = false;
    if ( *p == '+' )
    {
      p++;
    }
    while ( isdigit(*p) )
    {
      register uChar d = uChar((*p) - '0');
      if (  num > tenth_limit
         || (num == tenth_limit && d > tenth_limit_digit) )
      {
        overflow = true;
        break;
      }
      num = (num<<3)+(num<<1) + d;  // (10 * num) + d
      p++;
    }
    if ( overflow )
      num = ULONG_MAX;
  }
  return num;
}

//----------------------------------------------------------------------
FString FString::ltrim() const
{
  register wchar_t* p;
  FString s(this->string);

  // handle NULL and empty string
  if ( ! this->string || ! *this->string )
    return s;
  p = s.string;
  while ( iswspace(uInt(*p)) )
    p++;
  return FString(p);
}

//----------------------------------------------------------------------
FString FString::rtrim() const
{
  register wchar_t* p;
  register wchar_t* last;
  FString s(this->string);

  // handle NULL and empty string
  if ( ! this->string || ! *this->string )
    return s;
  p = s.string;
  last = p + length;
  while ( iswspace(uInt(*--last)) && last > p );
  if ( last == p && iswspace(uInt(*last)) )
    s.clear();
  else
    *(last+1) = '\0';

  return s;
}

//----------------------------------------------------------------------
FString FString::trim() const
{
  // handle NULL and empty string
  if ( ! this->string || ! *this->string )
    return (*this);
  FString s(this->ltrim());
  return s.rtrim();
}

//----------------------------------------------------------------------
FString FString::left(uInt len) const
{
  register wchar_t* p;
  FString s(this->string);

  // handle NULL and empty string
  if ( ! this->string || ! *this->string )
    return s;
  if ( len > length )
    return s;
  p = s.string;
  *(p+len) = '\0';
  return s;
}

//----------------------------------------------------------------------
FString FString::right(uInt len) const
{
  register wchar_t* p;
  FString s(this->string);

  // handle NULL and empty string
  if ( ! this->string || ! *this->string )
    return s;
  if ( len > length )
    return s;
  p = s.string;
  p += (length-len);
  return FString(p);
}

//----------------------------------------------------------------------
FString FString::mid(uInt pos, uInt len) const
{
  register wchar_t* p;
  register wchar_t* first;
  FString s(this->string);

  // handle NULL and empty string
  if ( ! this->string || ! *this->string )
    return s;
  if ( pos == 0 )
    pos = 1;
  if ( pos <= length && pos+len > length )
    len = length - pos + 1;
  if ( pos > length || pos+len-1 > length || len == 0 )
    return FString(L"");

  p = s.string;
  first = p + pos - 1;
  *(first+len) = '\0';
  return FString(first);
}

//----------------------------------------------------------------------
std::vector<FString> FString::split (const FString& delimiter)
{
  wchar_t* rest;
  wchar_t* token;
  FString s(this->string);
  std::vector<FString> stringList;

  // handle NULL and empty string
  if ( ! this->string || ! *this->string )
    return stringList;

  rest = 0;
  token = extractToken(&rest, s.string, delimiter.wc_str());

  while ( token )
  {
    stringList.push_back (FString(token));
    token = extractToken (&rest, 0, delimiter.wc_str());
  }
  return stringList;
}

//----------------------------------------------------------------------
FString& FString::setString (const wchar_t* s)
{
  _replace (s);
  return (*this);
}

//----------------------------------------------------------------------
FString& FString::setString (const char* s)
{
  const wchar_t* wc_str = c_to_wc_str(s);
  if ( wc_str )
  {
    _replace (wc_str);
    if ( *wc_str )
      delete[] wc_str;
  }
  return (*this);
}

//----------------------------------------------------------------------
FString& FString::setNumber (long num)
{
  register wchar_t* s;
  register bool neg;
  wchar_t buf[30];

  s = &buf[29];

  if ( num < 0 )
  {
    neg = true;
    num = -num;
  }
  else
  {
    neg = false;
  }
  *s = '\0';
  do
  {
    *--s = wchar_t(int(num%10) + '0');
    num /= 10;
  } while ( num );

  if ( neg )
    *--s = '-';
  _replace (s);
  return *this;
}

//----------------------------------------------------------------------
FString& FString::setNumber (uLong num)
{
  register wchar_t* s;
  wchar_t buf[30];

  s = &buf[29];
  *s = '\0';

  do
  {
    *--s = wchar_t(int(num%10) + '0');
    num /= 10;
  } while ( num );

  _replace (s);

  return *this;
}

//----------------------------------------------------------------------
FString& FString::setFormatedNumber (long num, char separator)
{
  register int n;
  register wchar_t* s;
  register bool neg;
  wchar_t buf[30];

  n = 0;
  s = &buf[29];

  if ( num < 0 )
  {
    neg = true;
    num = -num;
  }
  else
  {
    neg = false;
  }
  *s = L'\0';
  do
  {
    *--s = wchar_t(int(num%10) + '0');
    num /= 10;
    if ( num && ++n % 3 == 0 )
      *--s = separator;
  } while ( num );

  if ( neg )
    *--s = '-';
  _replace (s);
  return *this;
}

//----------------------------------------------------------------------
FString& FString::setFormatedNumber (uLong num, char separator)
{
  register int n;
  register wchar_t* s;
  wchar_t buf[30];

  n = 0;
  s = &buf[29];
  *s = L'\0';

  do
  {
    *--s = wchar_t(int(num%10) + '0');
    num /= 10;
    if ( num && ++n % 3 == 0 )
      *--s = separator;

  } while ( num );

  _replace (s);

  return *this;
}

// FString operators
//----------------------------------------------------------------------
bool FString::operator < (const FString& s) const
{
  if ( ! s )
    return false;
  if ( string && ! s.string )
    return false;
  if ( ! string && s.string )
    return true;
  if ( ! string && ! s.string )
    return false;
  return (wcscmp(string, s.string) < 0);
}

//----------------------------------------------------------------------
bool FString::operator <= (const FString& s) const
{
  if ( ! s )
    return false;
  if ( string && ! s.string )
    return false;
  if ( ! string && s.string )
    return true;
  if ( ! string && ! s.string )
    return true;
  return (wcscmp(string, s.string) <= 0);
}

//----------------------------------------------------------------------
bool FString::operator == (const FString& s) const
{
  if ( ! s )
    return false;
  if ( (string && ! s.string ) || (! string && s.string) )
    return false;
  if ( ! string && ! s.string )
    return true;
  return (wcscmp(string, s.string) == 0);
}

//----------------------------------------------------------------------
bool FString::operator != (const FString& s) const
{
  if ( ! s )
    return true;
  if ( (string && ! s.string ) || (! string && s.string) )
    return true;
  if ( ! string && ! s.string )
    return false;
  return (wcscmp(string, s.string) != 0);
}

//----------------------------------------------------------------------
bool FString::operator >= (const FString& s) const
{
  if ( ! s )
    return true;
  if ( string && ! s.string )
    return true;
  if ( ! string && s.string )
    return false;
  if ( ! string && ! s.string )
    return true;
  return (wcscmp(string, s.string) >= 0);
}

//----------------------------------------------------------------------
bool FString::operator > (const FString& s) const
{
  if ( ! s )
    return true;
  if ( string && ! s.string )
    return true;
  if ( ! string && s.string )
    return false;
  if ( ! string && ! s.string )
    return false;
  return (wcscmp(string, s.string) > 0);
}

//----------------------------------------------------------------------
const FString& FString::insert (const FString& s, uInt pos)
{
  // assert (pos <= length);
  if ( pos >= length )
    throw std::out_of_range("");
  _insert (pos, s.length, s.string);
  return (*this);
}

//----------------------------------------------------------------------
const FString& FString::insert (const wchar_t* s, uInt pos)
{
  // assert (pos <= length);
  if ( pos >= length )
    throw std::out_of_range("");
  _insert (pos, uInt(wcslen(s)), s);
  return (*this);
}

//----------------------------------------------------------------------
const FString& FString::insert (const char* s, uInt pos)
{
  return (insert(FString(s), pos));
}

//----------------------------------------------------------------------
const FString& FString::insert (const wchar_t c, uInt pos)
{
  return (insert(FString(c), pos));
}

//----------------------------------------------------------------------
const FString& FString::insert (const char c, uInt pos)
{
  return (insert(FString(c), pos));
}

//----------------------------------------------------------------------
FString FString::replace (const FString& from, const FString& to)
{
  register wchar_t* p;
  uInt from_length, to_length, pos;
  FString s(this->string);

  // handle NULL and empty string
  if ( ! this->string || ! *this->string )
    return s;
  if ( from.isNull() || to.isNull() )
    return s;
  p = s.string;
  from_length = from.getLength();
  to_length = to.getLength();
  pos = 0;
  while ( *p )
  {
    if ( wcsncmp(p, from.string, from_length) == 0 )
    {
      s._remove(pos, from_length);
      s._insert(pos, to_length, to.string);
      pos += to_length;
      p = s.string + pos;
    }
    else
    {
      pos++;
      p++;
    }
  }
  return s;
}

//----------------------------------------------------------------------
FString FString::replace (const FString& from, const std::wstring& to)
{
  FString to_str(to);
  return replace (from, to_str);
}

//----------------------------------------------------------------------
FString FString::replace (const FString& from, const wchar_t* to)
{
  FString to_str(to);
  return replace (from, to_str);
}

//----------------------------------------------------------------------
FString FString::replace (const FString& from, const std::string& to)
{
  FString to_str(to);
  return replace (from, to_str);
}

//----------------------------------------------------------------------
FString FString::replace (const FString& from, const char* to)
{
  FString to_str(to);
  return replace (from, to_str);
}

//----------------------------------------------------------------------
FString FString::replace (const FString& from, const wchar_t to)
{
  FString to_wchar(to);
  return replace (from, to_wchar);
}

//----------------------------------------------------------------------
FString FString::replace (const FString& from, const char to)
{
  FString to_char(to);
  return replace (from, to_char);
}

//----------------------------------------------------------------------
FString FString::replace (const std::wstring& from, const FString& to)
{
  FString from_str(from);
  return replace (from_str, to);
}

//----------------------------------------------------------------------
FString FString::replace (const std::wstring& from, const std::wstring& to)
{
  FString from_str(from);
  FString to_str(to);
  return replace (from_str, to_str);
}

//----------------------------------------------------------------------
FString FString::replace (const std::wstring& from, const wchar_t* to)
{
  FString from_str(from);
  FString to_str(to);
  return replace (from_str, to_str);
}

//----------------------------------------------------------------------
FString FString::replace (const std::wstring& from, const std::string& to)
{
  FString from_str(from);
  FString to_str(to);
  return replace (from_str, to_str);
}

//----------------------------------------------------------------------
FString FString::replace (const std::wstring& from, const char* to)
{
  FString from_str(from);
  FString to_str(to);
  return replace (from_str, to_str);
}

//----------------------------------------------------------------------
FString FString::replace (const std::wstring& from, const wchar_t to)
{
  FString from_str(from);
  FString to_wchar(to);
  return replace (from_str, to_wchar);
}

//----------------------------------------------------------------------
FString FString::replace (const std::wstring& from, const char to)
{
  FString from_str(from);
  FString to_char(to);
  return replace (from_str, to_char);
}

//----------------------------------------------------------------------
FString FString::replace (const std::string& from, const FString& to)
{
  FString from_str(from);
  FString to_str(to);
  return replace (from_str, to_str);
}

//----------------------------------------------------------------------
FString FString::replace (const std::string& from, const std::wstring& to)
{
  FString from_str(from);
  FString to_str(to);
  return replace (from_str, to_str);
}

//----------------------------------------------------------------------
FString FString::replace (const std::string& from, const wchar_t* to)
{
  FString from_str(from);
  FString to_str(to);
  return replace (from_str, to_str);
}

//----------------------------------------------------------------------
FString FString::replace (const std::string& from, const std::string& to)
{
  FString from_str(from);
  FString to_str(to);
  return replace (from_str, to_str);
}

//----------------------------------------------------------------------
FString FString::replace (const std::string& from, const char* to)
{
  FString from_str(from);
  FString to_str(to);
  return replace (from_str, to_str);
}

//----------------------------------------------------------------------
FString FString::replace (const std::string& from, const wchar_t to)
{
  FString from_str(from);
  FString to_wchar(to);
  return replace (from_str, to_wchar);
}

//----------------------------------------------------------------------
FString FString::replace (const std::string& from, const char to)
{
  FString from_str(from);
  FString to_char(to);
  return replace (from_str, to_char);
}

//----------------------------------------------------------------------
FString FString::replace (const wchar_t* from, const FString& to)
{
  FString from_str(from);
  return replace (from_str, to);
}

//----------------------------------------------------------------------
FString FString::replace (const wchar_t* from, const std::wstring& to)
{
  FString from_str(from);
  FString to_str(to);
  return replace (from_str, to_str);
}

//----------------------------------------------------------------------
FString FString::replace (const wchar_t* from, const wchar_t* to)
{
  FString from_str(from);
  FString to_str(to);
  return replace (from_str, to_str);
}

//----------------------------------------------------------------------
FString FString::replace (const wchar_t* from, const wchar_t to)
{
  FString from_str(from);
  FString to_wchar(to);
  return replace (from_str, to_wchar);
}

//----------------------------------------------------------------------
FString FString::replace (const wchar_t* from, const char to)
{
  FString from_str(from);
  FString to_char(to);
  return replace (from_str, to_char);
}

//----------------------------------------------------------------------
FString FString::replace (const char* from, const FString& to)
{
  FString from_str(from);
  FString to_str(to);
  return replace (from_str, to_str);
}

//----------------------------------------------------------------------
FString FString::replace (const char* from, const std::wstring& to)
{
  FString from_str(from);
  FString to_str(to);
  return replace (from_str, to_str);
}

//----------------------------------------------------------------------
FString FString::replace (const char* from, const wchar_t* to)
{
  FString from_str(from);
  FString to_str(to);
  return replace (from_str, to_str);
}

//----------------------------------------------------------------------
FString FString::replace (const char* from, const std::string& to)
{
  FString from_str(from);
  FString to_str(to);
  return replace (from_str, to_str);
}

//----------------------------------------------------------------------
FString FString::replace (const char* from, const char* to)
{
  FString from_str(from);
  FString to_str(to);
  return replace (from_str, to_str);
}

//----------------------------------------------------------------------
FString FString::replace (const char* from, const wchar_t to)
{
  FString from_str(from);
  FString to_wchar(to);
  return replace (from_str, to_wchar);
}

//----------------------------------------------------------------------
FString FString::replace (const char* from, const char to)
{
  FString from_str(from);
  FString to_char(to);
  return replace (from_str, to_char);
}

//----------------------------------------------------------------------
FString FString::replace (const wchar_t from, const FString& to)
{
  register wchar_t* p;
  FString s(this->string);

  // handle NULL and empty string
  if ( ! this->string || ! *this->string )
    return s;
  if ( to.isNull() )
    return s;
  p = s.string;
  uInt to_length = to.getLength();
  uInt pos = 0;
  while ( *p )
  {
    if ( wchar_t(*p) == from )
    {
      s._remove(pos, 1);
      s._insert(pos, to_length, to.wc_str());
      pos += to_length;
      p = s.string + pos;
    }
    else
    {
      pos++;
      p++;
    }
  }
  return s;
}

//----------------------------------------------------------------------
FString FString::replace (const wchar_t from, const std::wstring& to)
{
  FString to_str(to);
  return replace (from, to_str);
}

//----------------------------------------------------------------------
FString FString::replace (const wchar_t from, const wchar_t* to)
{
  FString to_str(to);
  return replace (from, to_str);
}

//----------------------------------------------------------------------
FString FString::replace (const wchar_t from, const std::string& to)
{
  FString to_str(to);
  return replace (from, to_str);
}

//----------------------------------------------------------------------
FString FString::replace (const wchar_t from, const char* to)
{
  FString to_str(to);
  return replace (from, to_str);
}

//----------------------------------------------------------------------
FString FString::replace (const wchar_t from, const wchar_t to)
{
  FString to_wchar(to);
  return replace (from, to_wchar);
}

//----------------------------------------------------------------------
FString FString::replace (const char from, const FString& to)
{
  FString from_str(from);
  return replace (from_str, to);
}

//----------------------------------------------------------------------
FString FString::replace (const char from, const std::wstring& to)
{
  FString from_str(from);
  FString to_str(to);
  return replace (from_str, to_str);
}

//----------------------------------------------------------------------
FString FString::replace (const char from, const wchar_t* to)
{
  FString from_str(from);
  FString to_str(to);
  return replace (from_str, to_str);
}

//----------------------------------------------------------------------
FString FString::replace (const char from, const std::string& to)
{
  FString from_str(from);
  FString to_str(to);
  return replace (from_str, to_str);
}

//----------------------------------------------------------------------
FString FString::replace (const char from, const char* to)
{
  FString from_str(from);
  FString to_str(to);
  return replace (from_str, to_str);
}

//----------------------------------------------------------------------
FString FString::replace (const char from, const wchar_t to)
{
  FString from_str(from);
  FString to_str(to);
  return replace (from_str, to_str);
}

//----------------------------------------------------------------------
FString FString::replace (const char from, const char to)
{
  register wchar_t* p;
  FString s(this->string);

  // handle NULL and empty string
  if ( ! this->string || ! *this->string )
    return s;

  p = s.string;
  while ( *p )
  {
    if ( char(*p) == from )
      *p = to;
    p++;
  }
  return s;
}

//----------------------------------------------------------------------
FString FString::replaceControlCodes() const
{
  register wchar_t* p;
  FString s(this->string);

  p = s.string;

  if ( p )
  {
    while ( *p )
    {
      if ( *p <= L'\x1f' )
      {
        *p += L'\x2400';
      }
      else if ( *p == L'\x7f' )
      {
        *p = L'\x2421';
      }
      else if ( *p >= L'\x80' && *p <= L'\x9f' )
      {
        *p = L' ';
      }
      else if ( ! iswprint(wint_t(*p)) )
        *p = L' ';
      p++;
    }
  }
  return s;
}

//----------------------------------------------------------------------
FString FString::expandTabs (uInt tabstop) const
{
  uLong end;
  FString instr(this->string);
  FString outstr("");

  std::vector<FString> tab_split = instr.split("\t");
  end = tab_split.size();
  for (uInt i=0; i < end; i++)
  {
    uInt len = tab_split[i].getLength();
    outstr += tab_split[i] + FString(tabstop - len % tabstop, L' ');
  }
  return outstr;
}

//----------------------------------------------------------------------
FString FString::removeDel() const
{
  register wchar_t* p;

  FString s(this->string);
  p = s.string;

  if ( p )
  {
    uInt i=0;
    uInt  d=0;
    while ( *p )
    {
      if ( *p == 0x7f )
      {
        d++;
      }
      else if ( d > 0 )
      {
        d--;
      }
      else
      {
        s.string[i] = *p;
        i++;
      }
      p++;
    }
    s.string[i] = L'\0';
    s.length = i;
  }
  return s;
}


//----------------------------------------------------------------------
FString FString::removeBackspaces() const
{
  register wchar_t* p;

  FString s(this->string);
  p = s.string;

  if ( p )
  {
    uInt i=0;
    while ( *p )
    {
      if ( *p != L'\b' )
      {
        s.string[i] = *p;
        i++;
      }
      else if ( i > 0 )
      {
        i--;
      }
      p++;
    }
    s.string[i] = L'\0';
    s.length = i;
  }
  return s;
}

//----------------------------------------------------------------------
const FString& FString::overwrite (const FString& s, uInt pos)
{
  if (length >= (pos + s.length))
  {
    wcsncpy(string + pos, s.string, s.length);
  }
  else
  {
    wcsncpy (string + pos, s.string, length - pos);
    _insert (length, pos + s.length - length, s.string + length - pos);
  }
  return (*this);
}

//----------------------------------------------------------------------
const FString& FString::overwrite (const wchar_t* s, uInt pos)
{
  uInt len = uInt(wcslen(s));
  if (length >= (pos+len) )
  {
    wcsncpy (string + pos, s, len);
  }
  else
  {
    wcsncpy (string + pos, s, length - pos);
    _insert (length, pos + len - length, s + length - pos);
  }
  return (*this);
}

//----------------------------------------------------------------------
const FString& FString::overwrite (const wchar_t c, uInt pos)
{
  if ( length >= (pos+1) )
  {
    string[pos] = c;
  }
  return (*this);
}

//----------------------------------------------------------------------
const FString& FString::remove (uInt pos, uInt len)
{
  assert ((pos < length) && ((pos + len) <= length));
  _remove (pos, len);
  return (*this);
}

//----------------------------------------------------------------------
bool FString::includes (const FString& s)
{
  return (wcsstr(string, s.string) != 0);
}

//----------------------------------------------------------------------
bool FString::includes (const wchar_t* s)
{
  return (wcsstr(string, s) != 0);
}

//----------------------------------------------------------------------
bool FString::includes (const char* s)
{
  bool ret;
  const wchar_t* wc_str = c_to_wc_str(s);
  if ( ! wc_str )
    return false;
  ret = bool(wcsstr(string, wc_str) != 0);
  if ( *wc_str )
    delete[] wc_str;
  return (ret);
}

//----------------------------------------------------------------------
bool FString::includes (const wchar_t c)
{
  wchar_t s[2];
  s[0] = c;
  s[1] = L'\0';
  return (wcsstr(string, s) != 0);
}

//----------------------------------------------------------------------
bool FString::includes (const char c)
{
  wchar_t s[2];
  s[0] = wchar_t(c & 0xff);
  s[1] = L'\0';
  return (wcsstr(string, s) != 0);
}