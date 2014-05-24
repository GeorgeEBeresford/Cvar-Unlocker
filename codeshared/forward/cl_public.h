/**
	\file
	
	Client-specific functions used by shared code.
	i.e. these functions differ in implementation between SP and MP.
	
	They are thus not implemented in the CommonLib & co, they'll be linked in when the libraries are linked into the client.
**/

#pragma once

#include "qcommon/q_platform.h"
#include "qcommon/q_sharedtypes.h"
#include "qcommon/qcommon_shared.h"

// This is a common subset of the SP and MP tags that is safe to use in shared code.
typedef enum
{
	TAG_FILESYS = 3,
	TAG_EVENT,
	TAG_CLIPBOARD
} memtag_shared_t;

// dito for Error Codes
typedef enum {
	ERR_FATAL,					// exit the entire game with a popup window
	ERR_DROP,					// print to console and disconnect from game
} errorParm_shared_t;

/**
	\brief Print a formatted string to the console. Format like printf.
**/
void QDECL Com_Printf( const char *format, ... );
void QDECL Com_DPrintf( const char *fmt, ... );
void QDECL Com_Error( int level, const char *error, ... );
int	QDECL Com_sprintf( char *dest, int size, const char *fmt, ... );

void Q_strcat( char *dest, int size, const char *src );
void Q_strncpyz( char *dest, const char *src, int destsize );
int Q_stricmp( const char *s1, const char *s2 );
int Q_strncmp( const char *s1, const char *s2, int n );

int FS_FilenameCompare( const char *s1, const char *s2 );
char *FS_BuildOSPath( const char *base, const char *game, const char *qpath );

void Com_Init( char *commandLine );
void Com_Frame( void );
void Com_GenerateEvent( void );
void Com_Shutdown( void );
int Com_FilterPath( const char *filter, const char *name, int casesensitive );
char *CopyString( const char *in ); // Z_Malloc's a string

qboolean CL_IsLoading( void );

void COM_BeginParseSession( const char *name );
void COM_EndParseSession( void );
char *COM_Parse( const char **data_p );
int Key_StringToKeynum( char *str );
int Com_HexStrToInt( const char *str );

int Z_Free( void *pvAddress );
void *Z_Malloc( int iSize, int eTag, qboolean bZeroit = qfalse, int iUnusedAlign = 4 );

int Key_GetCatcher( void );

// Edit fields and command line history/completion
// (These are probably the same between mp and sp and could go into CommonLib?)
void Field_Clear( field_t *edit );
void Field_AutoComplete( field_t *edit );
void Field_CompleteKeyname( void );
void Field_CompleteFilename( const char *dir, const char *ext, qboolean stripExt, qboolean allowNonPureFilesOnDisk );
void Field_CompleteCommand( char *cmd, qboolean doCommands, qboolean doCvars );


//    Console Commands

typedef void( *xcommand_t ) ( void );
void	Cmd_AddCommand( const char *cmd_name, xcommand_t function );
void	Cmd_RemoveCommand( const char *cmd_name );
int		Cmd_Argc( void );
char	*Cmd_Argv( int arg );


// Command Buffer

void Cbuf_ExecuteText( int exec_when, const char *text );


//    CVar

cvar_t *Cvar_Get( const char *var_name, const char *value, uint32_t flags );
cvar_t *Cvar_Set( const char *var_name, const char *value );
char *Cvar_VariableString( const char *var_name );
int Cvar_VariableIntegerValue( const char *var_name );