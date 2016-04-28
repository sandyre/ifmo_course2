// Приведенный ниже блок ifdef - это стандартный метод создания макросов, упрощающий процедуру 
// экспорта из библиотек DLL. Все файлы данной DLL скомпилированы с использованием символа SS_L3_LIBRARY_EXPORTS,
// в командной строке. Этот символ не должен быть определен в каком-либо проекте
// использующем данную DLL. Благодаря этому любой другой проект, чьи исходные файлы включают данный файл, видит 
// функции SS_L3_LIBRARY_API как импортированные из DLL, тогда как данная DLL видит символы,
// определяемые данным макросом, как экспортированные.
#ifdef SS_L3_LIBRARY_EXPORTS
#define SS_L3_LIBRARY_API __declspec(dllexport)
#else
#define SS_L3_LIBRARY_API __declspec(dllimport)
#endif

extern SS_L3_LIBRARY_API float FastInverseRoot ( float number );
