#include <gtk/gtk.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ctime>
namespace fs = std::filesystem;

static void list_folder (GtkWidget *widget, gpointer data)
{
  g_print ("List a folder\n");
  std::system("ls -l");
  // current datime
  time_t now = time(0);
  // converting to string
  char* dt = ctime(&now);
  std::cout << "local time: " << dt << "\n";
}

static void create_folder (GtkWidget *widget, gpointer data)
{
  g_print ("Create folders\n");
  fs::create_directory("new_folder_1");
  fs::create_directory("new_folder_2");
  std::system("ls -l");
}

static void delete_folder (GtkWidget *widget, gpointer data)
{
  g_print ("Delete folders\n");
  fs::remove_all("new_folder_1");
  fs::remove_all("new_folder_2");
  std::system("ls -l");
}

static void create_file (GtkWidget *widget, gpointer data)
{
  g_print ("Create a file\n");
  std::ofstream("./new_folder_1/test.txt");
  std::system("ls -l");
}

static void copy_file (GtkWidget *widget, gpointer data)
{
  g_print ("Copy a file\n");
  fs::path sourceFile = "./new_folder_1/test.txt";
  fs::path targetFile = "./new_folder_2/test.txt";
  fs::copy_file(sourceFile, targetFile, fs::copy_options::overwrite_existing);
  std::system("ls -l");
}

static void exit_app (GtkWidget *widget, gpointer data)
{
  g_print ("Exit app\n");
}

static void activate (GtkApplication* app, gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *box;

  //main window
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Menu");
  gtk_window_set_default_size (GTK_WINDOW (window), 600, 600);

  //box
  box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
  gtk_widget_set_halign (box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign (box, GTK_ALIGN_CENTER);
  gtk_window_set_child (GTK_WINDOW (window), box);
  
  //button
  button = gtk_button_new_with_label ("List a folder");
  g_signal_connect (button, "clicked", G_CALLBACK (list_folder), NULL);
  gtk_box_append (GTK_BOX (box), button);

  //button
  button = gtk_button_new_with_label ("Create forlders");
  g_signal_connect (button, "clicked", G_CALLBACK (create_folder), NULL);
  gtk_box_append (GTK_BOX (box), button);

  //button
  button = gtk_button_new_with_label ("Delete folders");
  g_signal_connect (button, "clicked", G_CALLBACK (delete_folder), NULL);
  gtk_box_append (GTK_BOX (box), button);

  //button
  button = gtk_button_new_with_label ("Create a file within new_folder_1");
  g_signal_connect (button, "clicked", G_CALLBACK (create_file), NULL);
  gtk_box_append (GTK_BOX (box), button);

  //button
  button = gtk_button_new_with_label ("Copy a file");
  g_signal_connect (button, "clicked", G_CALLBACK (copy_file), NULL);
  gtk_box_append (GTK_BOX (box), button);

  //button
  button = gtk_button_new_with_label ("Exit");
  g_signal_connect (button, "clicked", G_CALLBACK (exit_app), NULL);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_window_destroy), window);
  gtk_box_append (GTK_BOX (box), button);
  
  //show main window
  gtk_widget_show (window);
}

int main (int argc, char **argv)
{
  GtkApplication *app;
  int status;

  //app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  //app = gtk_application_new ("org.gtk.example", G_APPLICATION_GET_CLASS);
  app = gtk_application_new ("org.gtk.javier", G_APPLICATION_REPLACE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
