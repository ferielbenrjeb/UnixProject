#include <gtk/gtk.h>
#include <stdlib.h>
#include "serv_cli_fifo.h"
//fichier css pour window
void load_css(void)
{
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *scrw;
    // load css
    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    scrw = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(scrw, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gsize bytes_written, bytes_read;
    const gchar *file = "/home/ubuntu/Documents/ProjetUnix/style.css";
    GError *error = 0;
    gtk_css_provider_load_from_path(provider, g_filename_to_utf8(file, strlen(file), &bytes_read, &bytes_written, &error), NULL);
    g_object_unref(provider);
}
int main(int argc, char **argv)
{   //declaration de variable gtk
    GtkWidget *title1;
    GtkWidget *nombres;
    GtkWidget *window;
    GtkWidget *image1;
    GtkWidget *fixed;
    
 
    // ouverture de fichier et lecture de résultat
    
    char ch[50];
    char res[100] = "";
    resultat= fopen("test.txt", "r");
    // erreur d'ouverture
    if (resultat == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
    // lire chaine
    while (fgets(ch, 50, resultat))
    {

        strcat(res, ch);
    }
    // fermeture de fichier
    fclose(resultat);

    gtk_init(&argc, &argv);
       load_css();
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    title1 = gtk_label_new("********le résultat généré Avec les tubes********");
    nombres = gtk_label_new(res);
    image1 = gtk_image_new_from_file("inux1.png");
    
    gtk_fixed_put(GTK_FIXED(fixed), title1, 50, 50);
    gtk_fixed_put(GTK_FIXED(fixed), nombres, 70, 150);
    gtk_fixed_put(GTK_FIXED(fixed), image1, 500, 400);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_title(GTK_WINDOW(window), "Résultat Tube Window");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
