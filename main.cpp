#include <iostream>
#include <string>
#include <fstream>
#include <haru/hpdf.h>

using namespace std;

int main() {
    // Pedir al usuario que ingrese la ruta del archivo de texto
    string ruta_txt;
    cout << "Ingrese la ruta del archivo de texto (.txt): ";
    getline(cin, ruta_txt);

    // Abrir el archivo de texto
    ifstream archivo_txt(ruta_txt);
    if (!archivo_txt) {
        cerr << "Error: No se pudo abrir el archivo de texto." << endl;
        return 1;
    }

    // Crear un nuevo documento PDF
    HPDF_Doc pdf = HPDF_New(NULL, NULL);
    if (!pdf) {
        cerr << "Error: No se pudo crear el documento PDF." << endl;
        return 1;
    }

    // Crear una nueva página en el documento PDF
    HPDF_Page page = HPDF_AddPage(pdf);
    if (!page) {
        cerr << "Error: No se pudo agregar una página al documento PDF." << endl;
        HPDF_Free(pdf);
        return 1;
    }

    // Establecer el tamaño de la página
    HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_LETTER, HPDF_PAGE_PORTRAIT);

    // Crear una fuente
    HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", NULL);

    // Establecer la fuente y el tamaño del texto
    HPDF_Page_SetFontAndSize(page, font, 12);

    // Definir la posición inicial del texto
    float x = 50;
    float y = HPDF_Page_GetHeight(page) - 50;

    // Leer el archivo de texto y escribir su contenido en el documento PDF
    string linea;
    while (getline(archivo_txt, linea)) {
        HPDF_Page_BeginText(page);
        HPDF_Page_MoveTextPos(page, x, y);
        HPDF_Page_ShowText(page, linea.c_str());
        HPDF_Page_EndText(page);
        y -= 20; // Mover la posición del texto hacia arriba para la siguiente línea
    }

    // Guardar el documento PDF en un archivo
    string ruta_pdf = ruta_txt.substr(0, ruta_txt.find_last_of('.')) + ".pdf";
    if (HPDF_SaveToFile(pdf, ruta_pdf.c_str()) != HPDF_OK) {
        cerr << "Error: No se pudo guardar el documento PDF." << endl;
        HPDF_Free(pdf);
        return 1;
    }

    // Liberar memoria y cerrar el documento PDF y el archivo de texto
    HPDF_Free(pdf);
    archivo_txt.close();

    cout << "El archivo se ha convertido correctamente a PDF: " << ruta_pdf << endl;

    return 0;
}