#include <vector>
#include <iostream>
using namespace std;

int main() {
# if defined(__sgi)
	cout << "__sig"<<endl;
# endif


# if defined(__GNUC__)
	cout << "____GNUC__"<<endl;
	cout << __GNUC__ << ' ' << __GNUC_MINOR__ <<endl;
# endif

# ifdef __STL_NO_FRAND48
	cout << "__STL_NO_FRAND48 defined"<<endl;
# else
	cout << "__STL_NO_FRAND48 undefined"<<endl;
# endif

#ifdef __STL_STATIC_TEMPLATE_MEMBER_BUG
	cout << "__STL_STATIC_TEMPLATE_MEMBER_BUG defined" <<endl;
# else
	cout << "__STL_STATIC_TEMPLATE_MEMBER_BUG undefined" <<endl;
#endif

#ifdef __STL_CLASS_PARTIAL_SPECILIZATION
	cout << "__STL_CLASS_PARTIAL_SPECIALIZATION defined" << endl;
#else
	cout << "__STL_CLASS_PARTIAL_SPECIALIZATION undefined" << endl;
#endif
}
