
#include <gtk/gtk.h>

GtkWidget *window;
GtkWidget *vbox;
GtkWidget *do_split;
GtkWidget *split_box;
GtkWidget *splitter;
GtkWidget *text1;
GtkWidget *text2;

static void on_button_clicked(GtkWidget *widget, gpointer data)
{
  printf("You pressed 'Do Split'\n");
  if (text2 == nullptr) {
    printf("Building text2\n");
    text2 = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text2), GTK_WRAP_WORD);
    gtk_paned_add2(GTK_PANED(splitter), text2);
    gtk_widget_show_all(text2);
  }
}

int main(int argc, char *argv[])
{
  text2 = nullptr;
  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "dyn_resize");
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
  gtk_container_add(GTK_CONTAINER(window), vbox);

  do_split = gtk_button_new_with_label("Do Split");
  g_signal_connect(do_split, "clicked", G_CALLBACK(on_button_clicked), nullptr);
  gtk_box_pack_start(GTK_BOX(vbox), do_split, FALSE, FALSE, 0);


  split_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
  gtk_container_add(GTK_CONTAINER(vbox), split_box);

  splitter = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
  gtk_container_add(GTK_CONTAINER(split_box), splitter);

  text1 = gtk_text_view_new();
  gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text1), GTK_WRAP_WORD);

  gtk_paned_add1(GTK_PANED(splitter), text1);


  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}
