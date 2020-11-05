#include "widgets/InstructionsWidget.h"

#include <QScrollArea>
#include <QBoxLayout>

InstructionsWidget::InstructionsWidget(QWidget *parent) {
   setupGui();
}

void InstructionsWidget::setupGui() {
  auto *scroll_pane = new QScrollArea(this);
  instructions_label_ = new QLabel(scroll_pane);

  QString TEXT = "<html>"
                 "<body>"
                 "<div style=\"margin: 10px 10px 10px 10px\">"
                 "<table><tr>"
                 "<td style=\"padding-top: 15px;text-align: left;\"><h1>Willkommen bei </h1></td>"
                 "<td><img src=\":icons/light-logo.png\"/></td>"
                 "</tr></table>"
                 "<div style=\"margin-left: 10px\"><p>In diesem Tab findet sich eine kurze Anleitung für Erstbenutzer dieses Programms.</p></div>"
                 "<h2>Schnellstart</h2>"
                 "<div style=\"margin-left: 10px\"><p>Wenn du sofort loslegen willst, führe einfach folgende drei Schritte durch:</p></div>"
                 "<h2>Einloggen</h2>"
                 "<div style=\"margin-left: 10px\"><p>Klicke im Tab <u>Einstellungen</u> auf den Knopf auf den Knopf <u>Einloggen</u>. Kurz darauf wird sich dein Browser einloggen und du wirst aufgefordert, dich mit deiner Tim-Kennung zu authentifizieren. Danach musst du Sync-my-L²P authorisieren, damit das Programm auf deine Daten im L²P zugreifen kann. Sobald du auch dies erledigt hast, kannst du den Browser schließen und zum Programm zurückkehren.</p></div>"
                 "<h2>Daten aktualisieren und auswählen</h2>"
                 "<div style=\"margin-left: 10px\"><p>Nach dem erfolgreichen Login werden automatisch die Daten aller deiner Kurse im L²P abgerufen. Dies kann einen Moment dauern. Sobald die Aktualisierung fertig ist, kannst du die abgerufenen Daten ansehen und einzelne Dateien/Verzeichnisse/Kurse/Semester von dem Download ausschließen. Auch kannst du Filter für Größe und Änderungsdatum setzen.</p></div>"
                 "<h2Download</h2>"
                 "<div style=\"margin-left: 10px\"><p>Um nun deine Dateien runterzuladen musst du noch ein Downloadverzeichnis setzen. Hierfür klickst du im Tab <u>Einstellungen</u> auf den Knopf <u>Durchsuchen</u> und wählst ein Ordner aus. Nun musst du nur noch im Tab <u>Dateibrowser</u> auf den Knopf <u>Downloaden</u> drücken und Sync-my-L²P lädt alle ausgewählten Dateien für dich herrunter.</p></div>"
                 "<h2>Tips und Tricks</h2>"
                 "<div style=\"margin-left: 10px\"><p>Die <u>Farbe</u> der Dateien gibt dir Auskunft über den aktuellen Status der Dateien. Rot bedeutet <u>nicht downloaden</u>, Schwarz sind neue, nicht runtergeladene Dateien und Grün wird für bereits auf deiner Festplatte vorhandene Dateien benutzt.</p></div>"
                 "<div style=\"margin-left: 10px\"><p>Du kannst durch einen <u>Doppelklick</u> auf Dateien diese einfach öffnen.</p></div>"
                 "<div style=\"margin-left: 10px\"><p>Im Tab <u>Einstellungen</u> finden sich einige Optionen, mit denen du Sync-my-L²P noch komfortabler machen kannst.</p></div>"
                 "</div>"
                 "</body>"
                 "</html>";

  instructions_label_->setText(TEXT);
  instructions_label_->setWordWrap(true);
  instructions_label_->setAlignment(Qt::AlignJustify|Qt::AlignTop);
  scroll_pane->setWidget(instructions_label_);
  scroll_pane->setWidgetResizable(true);

  auto *layout = new QVBoxLayout(this);
  layout->addWidget(scroll_pane);
  layout->setContentsMargins(0,0,0,0);

  setLayout(layout);
}
