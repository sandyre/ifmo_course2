// ����������� ���� ���� ifdef - ��� ����������� ����� �������� ��������, ���������� ��������� 
// �������� �� ��������� DLL. ��� ����� ������ DLL �������������� � �������������� ������� SS_L3_LIBRARY_EXPORTS,
// � ��������� ������. ���� ������ �� ������ ���� ��������� � �����-���� �������
// ������������ ������ DLL. ��������� ����� ����� ������ ������, ��� �������� ����� �������� ������ ����, ����� 
// ������� SS_L3_LIBRARY_API ��� ��������������� �� DLL, ����� ��� ������ DLL ����� �������,
// ������������ ������ ��������, ��� ����������������.
#ifdef SS_L3_LIBRARY_EXPORTS
#define SS_L3_LIBRARY_API __declspec(dllexport)
#else
#define SS_L3_LIBRARY_API __declspec(dllimport)
#endif

extern SS_L3_LIBRARY_API float FastInverseRoot ( float number );
