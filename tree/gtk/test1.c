#include <gtk/gtk.h>

#include "root.xpm"
#include "server.xpm"

enum {
    COLUMN_ICON,
    COLUMN_TEXT,
    NUM_COLUMNS
};

static GtkTreeModel* create_and_fill_model(void)
{
  // Load XPM icons
  GdkPixbuf *root_pixbuf = gdk_pixbuf_new_from_xpm_data((const char **)root_xpm);
  GdkPixbuf *server_pixbuf = gdk_pixbuf_new_from_xpm_data((const char **)server_xpm);

  GtkTreeStore *treestore = gtk_tree_store_new(NUM_COLUMNS, GDK_TYPE_PIXBUF, G_TYPE_STRING);

  // Add a root item
  GtkTreeIter toplevel, child;
  gtk_tree_store_append(treestore, &toplevel, NULL);
  gtk_tree_store_set(treestore, &toplevel, COLUMN_TEXT, "Servers", -1);
  gtk_tree_store_set(treestore, &toplevel, COLUMN_ICON, root_pixbuf, -1);

  // Add child items
  gtk_tree_store_append(treestore, &child, &toplevel);
  gtk_tree_store_set(treestore, &child, COLUMN_TEXT, "Server 1", -1);
  gtk_tree_store_set(treestore, &child, COLUMN_ICON, server_pixbuf, -1);

  gtk_tree_store_append(treestore, &child, &toplevel);
  gtk_tree_store_set(treestore, &child, COLUMN_TEXT, "Server 2", -1);
  gtk_tree_store_set(treestore, &child, COLUMN_ICON, server_pixbuf, -1);

  g_object_unref(root_pixbuf);
  g_object_unref(server_pixbuf);

  return GTK_TREE_MODEL(treestore);
}

static GtkWidget* create_view_and_model(void) {
    GtkWidget *view;
    GtkTreeViewColumn *col;
    GtkCellRenderer *renderer;

    view = gtk_tree_view_new();
    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(view), FALSE);

    // Column for icon
    renderer = gtk_cell_renderer_pixbuf_new();
    col = gtk_tree_view_column_new_with_attributes("Icon", renderer, "pixbuf", COLUMN_ICON, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), col);

    // Column for text
    renderer = gtk_cell_renderer_text_new();
    col = gtk_tree_view_column_new_with_attributes("Text", renderer, "text", COLUMN_TEXT, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), col);

    // Set model and icons
    GtkTreeModel *model = create_and_fill_model();
    gtk_tree_view_set_model(GTK_TREE_VIEW(view), model);
    g_object_unref(model);

    return view;
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *view;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Tree View Example");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    view = create_view_and_model();

    // Initially expand all rows
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(view));
    GtkTreeIter iter;
    GtkTreePath *path;

    if (gtk_tree_model_get_iter_first(model, &iter)) {
        path = gtk_tree_model_get_path(model, &iter);
        gtk_tree_view_expand_row(GTK_TREE_VIEW(view), path, FALSE);
        gtk_tree_path_free(path);
    }

    gtk_container_add(GTK_CONTAINER(window), view);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}

