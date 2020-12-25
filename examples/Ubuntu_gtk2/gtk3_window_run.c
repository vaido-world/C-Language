#if 0
  set -e; 
  tcc -run `pkg-config --libs --cflags gtk+-3.0` "$0"
  exit
#endif

//#!/usr/bin/tcc -run -s pkg-config '--libs' '--cflags' gtk+-3.0

#include <gtk/gtk.h>

static void activate();

int
main (int    argc,
      char **argv)
{
  GtkApplication *application;
  gulong g_signal_status;
  int application_status;

  application         = gtk_application_new ("org.gtk.examples", G_APPLICATION_FLAGS_NONE);
  g_signal_status     = g_signal_connect(application, "activate", G_CALLBACK (activate), NULL);
  application_status  = g_application_run (G_APPLICATION (application), argc, argv);
  g_object_unref(application);

  return application_status;
}

static void
activate(GtkApplication* app,
          gpointer        user_data)
{
  GtkWidget *window;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 0);
  gtk_widget_show_all (window);
}
