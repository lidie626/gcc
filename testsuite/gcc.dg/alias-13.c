/* { dg-do compile } */
/* { dg-require-alias "" } */
/* { dg-options "-O2" } */
static void f (void) __attribute__((alias("g"))); static void g (void) __attribute__((alias("f"))); // { dg-error "part of alias cycle" }

void h ()
{
  f ();
}
