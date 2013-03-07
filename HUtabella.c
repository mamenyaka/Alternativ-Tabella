//Results from Wikipedia, replace "–" with "-"
#include <stdio.h>
#include <math.h>
#include <ctype.h>

#define CSAPATDB 16

int kereszt[CSAPATDB][CSAPATDB];
double L[CSAPATDB][CSAPATDB];
char *CSAP[CSAPATDB] = {
  "Budapest Honvéd",
  "Debreceni VSC",
  "Diósgyőr",
  "Ferencváros",
  "Győri ETO",
  "Haladás",
  "Kaposvári Rákóczi",
  "Kecskeméti TE",
  "Lombard Pápa",
  "Paksi FC",
  "Pécsi MFC",
  "BFC Siófok",
  "Újpest",
  "MTK Budapest",
  "Videoton",
  "Egri FC"
};

void
matrix1kiir (int A[CSAPATDB][CSAPATDB])
{
  int i, j;
  
  for (i = 0; i < CSAPATDB; i++)
    {
      for (j = 0; j < CSAPATDB; j++)
	if (i == j)
	  printf ("X ");
	else
	  printf ("%d ", A[i][j]);
      printf ("\n");
    }
  printf ("\n");
}

void
matrix2kiir (double A[CSAPATDB][CSAPATDB])
{
  int i, j;
  
  for (i = 0; i < CSAPATDB; i++)
    {
      for (j = 0; j < CSAPATDB; j++)
	printf ("%.3f ", A[i][j]);
      printf ("\n");
    }
  printf ("\n");
}

void
kiir (double hv[CSAPATDB], int a[CSAPATDB][CSAPATDB])
{
  FILE *fp = fopen ("kimhu", "w");

  struct csapat
  {
    char *nev;
    double szam;
    int pont;
  } csap[CSAPATDB], csap2[CSAPATDB];
  
  int i, j;

  for (i = 0; i < CSAPATDB; i++)
    {
      csap[i].nev = csap2[i].nev = CSAP[i];
      csap[i].szam = csap2[i].szam = hv[i];
      csap[i].pont = csap2[i].pont = 0;
    }

  for (i = 0; i < CSAPATDB; i++)
    for (j = 0; j < CSAPATDB; j++)
      if (a[i][j] == 1)
	csap[i].pont += 3;
      else if (a[i][j] == 2)
	{
	  csap[i].pont++;
	  csap[j].pont++;
	}
      else if (a[i][j] == 3)
	csap[j].pont += 3;

  struct csapat tmp;
  for (i = 0; i < CSAPATDB; i++)
    for (j = 0; j < CSAPATDB; j++)
    {
      if (csap[i].pont > csap[j].pont)
	{
	  tmp = csap[i];
	  csap[i] = csap[j];
	  csap[j] = tmp;
	}
      
      if (csap2[i].szam > csap2[j].szam)
	{
	  tmp = csap2[i];
	  csap2[i] = csap2[j];
	  csap2[j] = tmp;
	}
    }

  fprintf (fp, "{| {{széptáblázat}}\n! 2012/2013 NB1.\n! Pontszám\n! Alternatív tabella I.\n! Rangszám\n");

  for (i = 0; i < CSAPATDB; i++)
    {
      fprintf (fp, "|-\n");
      fprintf (fp, "| %s\n| %d\n", csap[i].nev, csap[i].pont);
      fprintf (fp, "| %s\n| %.4f\n", csap2[i].nev, csap2[i].szam);
    }

  for (i = 0; i < CSAPATDB; i++)
    {
      printf ("%s", csap[i].nev);
      for (j = slen (csap[i].nev); j <= 20; j++)
	printf (" ");
      printf ("%3d   %s", csap[i].pont, csap2[i].nev);
      for (j = slen (csap2[i].nev); j <= 20; j++)
	printf (" ");
      printf ("%.4f\n", csap2[i].szam);
    }

  fprintf (fp, "|-\n|}");
}

int
slen (char *szo)
{
  int db = 0, k = 0, db2 = 0;
  
  while (szo[k] != '\0')
    {
      if (isalpha (szo[k]))
	{
	  if (db2 != 0)
	    db += db2 / 2;
	  db++;
	  db2 = 0;
	}
      else if (szo[k] == ' ')
	db++;
      else
	db2++;
	
      k++;
    }

  return db;
}

void
matrix1 ()
{
  int db = 0, c, k, mehet = 0, csap1, csap2, a, b, ered, i, j;
  char csapat[20];
  char *p;

  while ((c = getchar ()) != EOF)
    {
      if (c == '\n')
	mehet++;
      if (mehet == 2)
	{
	  mehet = 0;
	  for (j = 0; j < 8; j++)
	    {
	      k = 0;
	      while ((c = getchar ()) != '\t')
		csapat[k++] = c;
	      csapat[k] = '\0';
	      p = csapat;
	      for (i = 0; i < CSAPATDB; i++)
		if (strcmp (CSAP[i], p) == 0)
		  csap1 = i;

	      a = getchar ();
	      getchar ();
	      b = getchar ();

	      if (a > b)
		ered = 1;
	      else if (a == b)
		ered = 2;
	      else if (a < b)
		ered = 3;
	      getchar ();

	      k = 0;
	      while ((c = getchar ()) != '\n')
		csapat[k++] = c;
	      csapat[k] = '\0';
	      p = csapat;
	      for (i = 0; i < CSAPATDB; i++)
		if (strcmp (CSAP[i], p) == 0)
		  csap2 = i;

	      db++;
	      kereszt[csap1][csap2] = ered;
	    }
	}
    }

  printf ("%d. fordulo, %d meccs lejatszva\n\n", db / (CSAPATDB / 2), db);
  matrix1kiir (kereszt);
}

void
matrix2 ()
{
  int pontotSzerez[CSAPATDB][CSAPATDB];
  int i, j;

  for (i = 0; i < CSAPATDB; i++)
    for (j = 0; j < CSAPATDB; j++)
      pontotSzerez[i][j] = 0;

  for (i = 0; i < CSAPATDB; i++)
    for (j = 0; j < CSAPATDB; j++)
      if (kereszt[i][j] == 1)
	pontotSzerez[i][j]++;
      else if (kereszt[i][j] == 2)
	{
	  pontotSzerez[i][j]++;
	  pontotSzerez[j][i]++;
	}
      else if (kereszt[i][j] == 3)
	++pontotSzerez[j][i];

  int oszlopOsszeg[CSAPATDB];
  int o;

  for (i = 0; i < CSAPATDB; i++)
    {
      o = 0;
      for (j = 0; j < CSAPATDB; j++)
	o += pontotSzerez[j][i];
      oszlopOsszeg[i] = o;
    }

  for (i = 0; i < CSAPATDB; i++)
    for (j = 0; j < CSAPATDB; j++)
      if (oszlopOsszeg[j] != 0.0)
	L[i][j] = pontotSzerez[i][j] * (1.0 / oszlopOsszeg[j]);
      else
	L[i][j] = pontotSzerez[i][j];
}

int
main ()
{
  int i, j;
  
  for (i = 0; i < CSAPATDB; i++)
    for (j = 0; j < CSAPATDB; j++)
      kereszt[i][j] = 0;

  matrix1 ();
  matrix2 ();

  double hv[CSAPATDB];
  double h[CSAPATDB];

  for (i = 0; i < CSAPATDB; i++)
    {
      hv[i] = 1.0 / CSAPATDB;
      h[i] = 0.0;
    }

  double reginorma = 0.0, regiosszeg = 0.0;

  int amig = 1;
  double osszeg, norma, osszegEll, d;

  while (amig)
    {
      for (i = 0; i < CSAPATDB; i++)
	for (j = 0; j < CSAPATDB; j++)
	  h[i] += L[i][j] * hv[j];

      osszeg = 0.0;
      for (i = 0; i < CSAPATDB; i++)
	osszeg += (hv[i] - h[i]) * (hv[i] - h[i]);

      norma = sqrt (osszeg);

      if (norma < 0.000000000001)
	{
	  amig = 0;

	  osszegEll = 0.0;
	  for (i = 0; i < CSAPATDB; i++)
	    osszegEll += h[i];
	}

      d = 0.87;

      osszeg = 0.0;
      for (i = 0; i < CSAPATDB; i++)
	{
	  hv[i] = d * h[i] + (1.0 - d) / CSAPATDB;
	  osszeg += hv[i];
	  h[i] = 0.0;
	}

      if (osszeg == regiosszeg && norma == reginorma)
	amig = 0;

      reginorma = norma;
      regiosszeg = osszeg;
    }

  kiir (hv, kereszt);
  
  return 0;
}
