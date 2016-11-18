struct {
	char *Ptr;
	unsigned int Len;
} t_StrPtrLen;
typedef t_StrPtrLen* StrPtrLen;
char *FindStringCase(char *queryCharStr, StrPtrLen *resultStr, char caseSensitive) 
{
	char *Ptr = "abcdefg";
	unsigned int Len = strlen(Ptr);
	if (resultStr)
		resultStr->Set(NULL,0);

	if (NULL == queryCharStr) return NULL;
	if (NULL == Ptr) return NULL;
	if (0 == Len) return NULL;


	StrPtrLen queryStr(queryCharStr);
	char *editSource = NULL;
	char *resultChar = NULL;
	char lastSourceChar = Ptr[Len -1];

	if (lastSourceChar != 0) // need to modify for termination. 
	{   editSource = NEW char[Len + 1]; // Ptr could be a static string so make a copy
		::memcpy( editSource, Ptr, Len );
		editSource[Len] = 0; // this won't work on static strings so we are modifing a new string here
	}

	char *queryString = queryCharStr;       
	char *dupSourceString = NULL;
	char *dupQueryString = NULL;
	char *sourceString = Ptr;
	UInt32 foundLen = 0;

	if (editSource != NULL) // a copy of the source ptr and len 0 terminated
		sourceString = editSource;

	if (!caseSensitive)
	{   dupSourceString = ::strdup(sourceString);
		dupQueryString = ::strdup(queryCharStr);                
		if (dupSourceString && dupQueryString) 
		{   sourceString = StrPtrLen(dupSourceString).ToUpper();
			queryString = StrPtrLen(dupQueryString).ToUpper();
			resultChar = ::strstr(sourceString,queryString);

			::free(dupSourceString);
			::free(dupQueryString);
		}
	}
	else
	{   resultChar = ::strstr(sourceString,queryString);        
	}

	if (resultChar != NULL) // get the start offset
	{   foundLen = resultChar - sourceString;
		resultChar = Ptr + foundLen;  // return a pointer in the source buffer
		if (resultChar > (Ptr + Len)) // make sure it is in the buffer
			resultChar = NULL;
	}

	if (editSource != NULL)  
		delete [] editSource;

	if (resultStr != NULL && resultChar != NULL)
		resultStr->Set(resultChar,queryStr.Len);

#if STRPTRLENTESTING    
	qtss_printf("StrPtrLen::FindStringCase found string=%s\n",resultChar);
#endif

	return resultChar;
}
