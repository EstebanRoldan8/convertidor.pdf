#include <iostream>
#include <string>
#include <podofo/podofo.h>

class ConvertidorPDF {
public:
    ConvertidorPDF() {
        archivo_seleccionado = "";
    }

    void seleccionarArchivo(const std::string& archivo) {
        archivo_seleccionado = archivo;
    }

    void convertirAPDF() {
        if (archivo_seleccionado.empty()) {
            std::cout << "No se ha seleccionado ningún archivo." << std::endl;
            return;
        }

        try {
            PoDoFo::PdfDocument pdf;
            pdf.Create("archivo.pdf");

            PoDoFo::PdfPage* page = pdf.CreatePage(PoDoFo::PdfPage::CreateStandardPageSize(PoDoFo::ePdfPageSize_A4));
            pdf.InsertPage(page);

            PoDoFo::PdfPainter painter;
            painter.SetPage(page);

            PoDoFo::PdfFont font = pdf.CreateFont("Arial");
            painter.SetFont(&font, 12);

            std::ifstream archivo_txt(archivo_seleccionado);
            std::string linea;

            while (std::getline(archivo_txt, linea)) {
                painter.DrawText(50, 750, linea.c_str());
            }

            pdf.Close();

            std::cout << "Archivo convertido a PDF exitosamente." << std::endl;

        } catch (const PoDoFo::PdfError& e) {
            std::cout << "Error: " << e.GetError() << std::endl;
        }
    }

private:
    std::string archivo_seleccionado;
};

int main() {
    ConvertidorPDF convertidor;

    std::string archivo;
    std::cout << "Ingrese la ruta del archivo de texto (.txt): ";
    std::getline(std::cin, archivo);

    convertidor.seleccionarArchivo(archivo);
    convertidor.convertirAPDF();

    return 0;
}