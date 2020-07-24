/* See the "license" file. */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *argv0;


unsigned int tmplc;
char **tmplv;
char *tmplk[256];
char *tmpl;

void
usage(void)
{
	fprintf(stderr, "Usage: %s [tmpl] [strings]\n", argv0);
	exit(1);
}

void
die(int code, char *e)
{
	fprintf(stderr, "%s: fatal: %s\n", argv0, e);
	exit(code);
}

int
hasrepchrs(char *s)
{
	int i, j, l;
	l = strlen(s) ;
	for( i=0 ; i<l ; ++i )
		for( j=0 ; j<l ; ++j )
			if( s[i]==s[j] && i!=j )
				return 1 ;
	return 0 ;
}

void
main(int argc, char *argv[])
{
	int i;
	char buf[BUFSIZ];
	char *p;
	argv0 = argv[0] ;

	if(argc<3)
		usage();

	tmplc = argc - 2 ;
	tmplv = argv + 2 ;
	tmpl = argv[1] ;

	if( tmplc<strlen(tmpl) )
		die(1, "count of chars in template is more than amount of strings");

	if(hasrepchrs(tmpl))
		die(1, "template contains repeated char");

	if(strchr(tmpl, '\n'))
		die(1, "template contains new line char");

	for( i=0 ; i<tmplc ; ++i )
		tmplk[tmpl[i]] = tmplv[i] ;

	while(fgets(buf, sizeof(buf), stdin)){
		p = buf ;
		while( *p!='\n' ){
			if(strchr(tmpl, *p))
				printf("%s", tmplk[*p]);
			else
				fprintf(stderr, "%s: warning: '%c': template has no such character\n", argv0, *p);
			++p;
		}
		puts("");
	}
}
