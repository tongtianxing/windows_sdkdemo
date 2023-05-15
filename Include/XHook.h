#pragma once


class CXHook
{
public:
	CXHook();

public:
	static void InitHook();

	static void ReleaseHook();

protected:
	static LRESULT CALLBACK GetMessageProc(int nCode, WPARAM wParam, LPARAM lParam);
private:
};