#include "qmlwatcher.h"

#include <QQuickItem>
#include <QQmlComponent>
#include <QQmlContext>
#include <QQmlProperty>
#include <QQmlEngine>

#include "live/hookcontainer.h"
#include "live/project.h"
#include "live/projectdocument.h"
#include "live/viewengine.h"
#include "live/visuallogqt.h"
#include "live/componentdeclaration.h"

namespace lv{

QmlWatcher::QmlWatcher(QObject *parent)
    : QObject(parent)
    , m_isEnabled(true)
    , m_componentComplete(false)
    , m_target(nullptr)
{
}

QmlWatcher::~QmlWatcher(){
}

void QmlWatcher::initialize(ViewEngine *, HookContainer *hooks, const QString &refFile, const QString &declaredId){
    if ( m_componentComplete )
        return;

    m_referencedFile = refFile;
    m_declaredId     = declaredId;

    hooks->insertKey(m_referencedFile, m_declaredId, this);
    m_componentComplete = true;
}

void QmlWatcher::componentComplete(){
    m_componentComplete = true;

    if ( !m_target )
        m_target = parent();

    ViewEngine* ve = ViewEngine::grab(this);

    QQmlContext* ctx = qmlContext(this);
    if ( !ctx )
        return;

    if ( m_declaredId.isEmpty() )
        m_declaredId = ctx->nameForObject(m_target);

    if ( m_declaredId.isEmpty() )
        return;

    ComponentDeclaration cd = ve->rootDeclaration(m_target);
    m_referencedFile = cd.url().toLocalFile();

    if ( checkChildDeclarations() ){
        HookContainer* hk = qobject_cast<HookContainer*>(ctx->contextProperty("hooks").value<QObject*>());
        hk->insertKey(m_referencedFile, m_declaredId, this);
    }

    emit ready();
}

bool QmlWatcher::checkChildDeclarations(){
    QQmlProperty pp(m_target);
    if ( pp.propertyTypeCategory() == QQmlProperty::List ){
        QQmlListReference assignmentList = qvariant_cast<QQmlListReference>(pp.read());
        for ( int i = 0; i < assignmentList.count(); ++i ){
            QObject* obj = assignmentList.at(i);
            QString localUrl = qmlContext(obj)->baseUrl().toLocalFile();
            if ( m_referencedFile != localUrl )
                return false;
        }
    }
    return true;
}

void QmlWatcher::setSingleton(QObject *singleton){
    if ( m_componentComplete ){
        ViewEngine* ve = ViewEngine::grab(this);
        if ( ve ){
            QmlError(
                ve,
                CREATE_EXCEPTION(lv::Exception, "QmlWatcher: Watcher already initialized. Cannot set singleton afterwards.", Exception::toCode("Completed")),
                this
            ).jsThrow();
        }
        return;
    }

    m_target = singleton;
    m_declaredId = "__singleton__";
    emit targetChanged();
}

}// namespace

