#include <QBoxLayout>
#include <QLabel>
#include <QTabWidget>
#include <QPlainTextEdit>

#include "issuetextview.h"
#include "markdown.h"
#include "markdowneditor.h"
#include "helpers/OriWidgets.h"
#include "helpers/OriLayouts.h"

using namespace Ori::Layouts;

MarkdownEditor::MarkdownEditor(const QString &editorTabTitle, QWidget *parent) : QWidget(parent)
{
    _editor = new QPlainTextEdit;
    Ori::Gui::adjustFont(_editor);

    _preview = new IssueTextView;

    auto editorTab = new QWidget;
    LayoutV({_editor, makeHintLabel()}).setMargin(Ori::Gui::layoutSpacing()).useFor(editorTab);

    auto previewTab = new QWidget;
    LayoutV({_preview}).setMargin(Ori::Gui::layoutSpacing()).useFor(previewTab);

    _tabs = new QTabWidget;
    connect(_tabs, &QTabWidget::currentChanged, this, &MarkdownEditor::tabSwitched);
    _tabIndexEditor = _tabs->addTab(editorTab, editorTabTitle.isEmpty()? tr("Edit"): editorTabTitle);
    _tabIndexPreview = _tabs->addTab(previewTab, tr("Preview"));

    LayoutH({_tabs}).setMargin(0).setSpacing(0).useFor(this);
}

QLabel* MarkdownEditor::makeHintLabel()
{
    auto label = new QLabel(Markdown::hint());
    auto palette = label->palette();
    auto color = palette.color(QPalette::WindowText);
    color.setAlpha(80);
    palette.setColor(QPalette::WindowText, color);
    label->setPalette(palette);
    return label;
}

bool MarkdownEditor::isModified() const
{
    return _editor->document()->isModified();
}

QString MarkdownEditor::getText() const
{
    return _editor->toPlainText().trimmed();
}

void MarkdownEditor::setFocus()
{
    _tabs->setCurrentIndex(_tabIndexEditor);
    _editor->setFocus();
}

void MarkdownEditor::tabSwitched(int tabIndex)
{
    if (tabIndex == _tabIndexPreview)
        _preview->setHtml(Markdown::process(sanitizeHtml(_editor->toPlainText())));
}
