#include <gtk/gtk.h>
void load_css(void)
{
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;
    const gchar *file = "style.css";
    GFile *css_fp = g_file_new_for_path(file);
    GError *error = 0;
    // load css
    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_css_provider_load_from_file(provider, css_fp, &error);
    g_object_unref(provider);
}
void button1_click()
{
    //cette commande permet de run excecutale de client.c et clientWtube.c 
    system("/home/ubuntu/Documents/ProjetUnix/Tube/buildTube/tube_run.sh");
}
void button2_click()
{   //cette commande permet de run excecutable de client.c de tcp et clientW.c de tcp
    system("/home/ubuntu/Documents/ProjetUnix/TCP/buildTCP/socket_run.sh");
}
int main(int argc, char **argv)
{   //declaration de variable de gtk
    GtkWidget *window;
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *fixed;
    GtkWidget *image;
    GtkWidget *image1;
    GtkWidget *Label;
    gchar *msg = NULL;
    gtk_init(&argc, &argv);
    //system permet de run en terminal 2 serveur
    system("gnome-terminal -e 'sh -c \"gcc -o /home/ubuntu/Documents/ProjetUnix/Tube/serveur /home/ubuntu/Documents/ProjetUnix/Tube/serveur.c && /home/ubuntu/Documents/ProjetUnix/Tube/serveur\"'");
    system("gnome-terminal -e 'sh -c \"gcc -o /home/ubuntu/Documents/ProjetUnix/TCP/server /home/ubuntu/Documents/ProjetUnix/TCP/server.c && /home/ubuntu/Documents/ProjetUnix/TCP/server\"'");
    load_css();
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    fixed = gtk_fixed_new();
    msg = g_locale_to_utf8("BIENVENUE DANS NOTRE APPLICATION ", -1, NULL, NULL, NULL); 
    Label = gtk_label_new(msg);                                                                 
    gtk_label_set_justify(GTK_LABEL(Label), GTK_JUSTIFY_CENTER);
    gtk_container_add(GTK_CONTAINER(window), fixed);
    
    button1 = gtk_button_new_with_label("Communication avec  tubes nommé");
    button2 = gtk_button_new_with_label("  Communication avec  sockets mode Tcp  ");
    gtk_widget_set_size_request(GTK_WIDGET(button1), 80, 70);
    gtk_widget_set_size_request(GTK_WIDGET(button2), 80, 70);

    gtk_container_add(GTK_CONTAINER(window), fixed);
    // image
    image = gtk_image_new_from_file("serveur.jpg");
    image1 = gtk_image_new_from_file("inux1.png");
    gtk_fixed_put(GTK_FIXED(fixed),Label, 150, 50);
    gtk_fixed_put(GTK_FIXED(fixed), button1,150, 300);
    gtk_fixed_put(GTK_FIXED(fixed), button2,150, 400);
    gtk_fixed_put(GTK_FIXED(fixed), image, 150, 100);
    gtk_fixed_put(GTK_FIXED(fixed), image1, 600, 400);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_title(GTK_WINDOW(window), "Acceuil");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 500);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    // event handler on button
    g_signal_connect_swapped(button1, "clicked", G_CALLBACK(button1_click), window);
    g_signal_connect_swapped(button2, "clicked", G_CALLBACK(button2_click), window);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
