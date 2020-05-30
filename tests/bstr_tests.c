#include "minunit.h"
#include <string.h>
#include <lcthw/bstrlib.h>

char *test_bfromcstr() {
    char *c_str = "Hola a todos";
    bstring b;

    b = bfromcstr(c_str);
    mu_assert(strcmp((const char*)b->data, c_str) == 0, 
        "bstring data is not equal to c_str data");

    bdestroy(b);
    return NULL;
}

char *test_blk2bstr() {
    char *c_str = "blk2bstr";
    int len = 9;

    bstring b;
    b = blk2bstr(c_str, len);
    

    mu_assert(strcmp((const char*)b->data, c_str) == 0, 
        "bstring data is not equal to c_str data");    

    bdestroy(b);
    return NULL;
}

char *test_bstricmp() {
    bstring bs1 = bfromcstr("Prueba_X");
    bstring bs2 = bfromcstr("Prueba_X");

    mu_assert(bstricmp(bs1, bs2) == 0, "bstrings are not equal.");

    bdestroy(bs1);
    bdestroy(bs2);
    return NULL;
}

char *test_bstrcpy() {
    bstring src = bfromcstr("Prueba copia.");
    bstring dest = bstrcpy(src);

    mu_assert(bstricmp(src, dest) == 0, "failed to copy src.");

    bdestroy(src);
    bdestroy(dest);
    return NULL;
}

char *test_bassign() {
    bstring bs1 = bfromcstr("");
    bstring bs2 = bfromcstr("Prueba_XYZ");

    bassign(bs1, bs2);
    mu_assert(bstricmp(bs1, bs2) == 0, "failed to assign bs2 in bs1");

    bdestroy(bs1);
    bdestroy(bs2);
    return NULL;
}

char *test_bassignblk() {
    bstring bstr = bfromcstr("");
	bassignblk(bstr, "hello", 2);
	
	char *cstr = bstr2cstr(bstr, 0);
	mu_assert(strcmp("he", cstr) == 0, 
			  "failed bassignblk normal case");

    bdestroy(bstr);
    bcstrfree(cstr);
    return NULL;
}

char *test_bdestroy() {
    bstring bs = bfromcstr("Prueba de bsdestroy");

    int rc = bdestroy(bs);
    mu_assert(rc == BSTR_OK, "Can not destroy bstring.");

    return NULL;
}

char *test_bconcat() {
    bstring bs1 = bfromcstr("Hello ");
    bstring bs2 = bfromcstr("world");
    bconcat(bs1, bs2);

    char *test = bstr2cstr(bs1, 0);

    mu_assert(strcmp("Hello world", test) == 0, "Failed concatenation.");

    bdestroy(bs1);
    bdestroy(bs2);
    bcstrfree(test);
    return NULL;
}

char *test_biseq() {
    bstring bs1 = bfromcstr("Es lo mismo.");
    bstring bs2 = bfromcstr("Es lo mismo.");

    mu_assert(biseq(bs1, bs2) == 1, "bstrings are not the same.");

    bdestroy(bs1);
    bdestroy(bs2);
    return NULL;
}

char *test_binstr() {
    bstring bs1 = bfromcstr("It is here");
    bstring bs2 = bfromcstr("is");

    mu_assert(binstr(bs1, 0, bs2) != BSTR_ERR, "bs2 is not in bs1");

    bdestroy(bs1);
    bdestroy(bs2);
    return NULL;
}

char *test_bfindreplace() {
    bstring bs1 = bfromcstr("It is here");
    bstring bs2 = bfromcstr("is");
    bstring bs3 = bfromcstr("is not");

    bfindreplace(bs1, bs2, bs3, 0);
    char *test = bstr2cstr(bs1, 0);

    mu_assert(strcmp(test, "It is not here") == 0, "Failed replacing.");

    bdestroy(bs1);
    bdestroy(bs2);
    bdestroy(bs3);
    bcstrfree(test);
    return NULL;
}

char *test_bformat() {
	bstring bstr;
	char *cstr;
	
	bstr = bformat("%s %s", "Hello", "world");
	cstr = bstr2cstr(bstr, 0);

	mu_assert(strcmp("Hello world", cstr) == 0,
			  "failed bformat");

	bdestroy(bstr);
	bcstrfree(cstr);
	
	return NULL;
}

char *test_bsplit() {
	bstring bstr;
	struct bstrList *list;
	char *cstr1;
	char *cstr2;
		
	bstr = bfromcstr("Hello world");
	list = bsplit(bstr, ' ');

	cstr1 = bstr2cstr(list->entry[0], 0);
	cstr2 = bstr2cstr(list->entry[1], 0);
	mu_assert(strcmp("Hello", cstr1) == 0, "failed bsplit index 0");
	mu_assert(strcmp("world", cstr2) == 0, "failed bsplit index 1");

	bdestroy(bstr);
	bcstrfree(cstr1);
	bcstrfree(cstr2);
	bstrListDestroy(list);

	return NULL;
}

char *test_bdata_char() {
	bstring bstr;
	char *cstr;
		
	bstr = bfromcstr("Hello world");

	cstr = bdata(bstr);
	mu_assert(strcmp("Hello world", cstr) == 0, "failed bdata");
	
	char firstCh = bchar(bstr, 0);
	char invalidCh = bchar(bstr, blength(bstr) + 1);
	mu_assert(firstCh == 'H', "failed bchar normal case");
	mu_assert(invalidCh == '\0', "failed bchar invalid case");

	bdestroy(bstr);

	return NULL;
}


char *all_tests() {
    mu_suite_start();

    mu_run_test(test_bfromcstr);
    mu_run_test(test_blk2bstr);
    mu_run_test(test_bstricmp);
    mu_run_test(test_bstrcpy);
    mu_run_test(test_bassign);
    mu_run_test(test_bassignblk);
    mu_run_test(test_bdestroy);
    mu_run_test(test_bconcat);
    mu_run_test(test_biseq);
    mu_run_test(test_binstr);
    mu_run_test(test_bfindreplace);
    mu_run_test(test_bformat);
    mu_run_test(test_bsplit);
    mu_run_test(test_bdata_char);

    return NULL;
}

RUN_TESTS(all_tests);