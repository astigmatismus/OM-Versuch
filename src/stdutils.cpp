#include <stdutils.h>
#include <iostream>
#include <vector>
// ---------------------------------------------------------------------------

using namespace std;
// ---------------------------------------------------------------------------

template<class T>
void	Print(const std::vector<T> &v, std::string text)
{
	typename vector<T>::const_iterator iv;
	
	//setlocale(LC_NUMERIC, "De_DE");
        cout.imbue( locale("German") );
	cout << setprecision(8) << setiosflags(ios_base::scientific | ios_base::showpos);
//	cout << setprecision(8) << setiosflags(ios_base::showpos);
	cout << text << endl;
	for ( iv = v.begin( ) ; iv != v.end( ) ; iv++ )
		cout << " " << *iv;
	cout << endl;
	cout << resetiosflags(ios_base::scientific | ios_base::showpos);
        cout.imbue( locale("C") );
	//setlocale(LC_NUMERIC, "C");
}
// ---------------------------------------------------------------------------

template <class T>
std::ostream&		operator<<	(std::ostream &s, const std::vector<T> &v)
{
	typename vector<T>::const_iterator iv;

	if (v.size()== 0)
		return s;

	//setlocale(LC_NUMERIC, "De_DE");
        s.imbue( locale("German") );
	s << setiosflags(ios_base::scientific | ios_base::showpos) << setprecision(3);
//	s << setw(8) << setprecision(3) << setiosflags(ios_base::showpos);

	for ( iv = v.begin( ) ; iv != v.end( )-1; iv++ )
		s << *iv << "\t";
	s << *iv;

//	s << endl;
	s << resetiosflags(ios_base::scientific | ios_base::showpos);
        s.imbue( locale("C") );
	//setlocale(LC_NUMERIC, "C");

	return s;
}
// ---------------------------------------------------------------------------

