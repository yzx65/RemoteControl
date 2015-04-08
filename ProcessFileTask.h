//---------------------------------------------------------------------------

#ifndef ProcessFileTaskH
#define ProcessFileTaskH
//---------------------------------------------------------------------------


extern DWORD WINAPI ProcessDirInfo(PVOID pContext);
extern DWORD WINAPI ProcessSearchInfo(PVOID pContext);
extern DWORD WINAPI ProcessPluginData(PVOID pContext);
extern VOID SendMessageToTarControlFrm(Target *tarBlock,
                                       UINT Msg,
                                       WPARAM wParam,
                                       LPARAM lParam);

void __fastcall ProcessUserPluginData(FileTask *lpFileTask, Target    *tarBlock);
void ProcessBackSoundPluginData(FileTask* lpFileTask, Target* tarBlock);

#endif
