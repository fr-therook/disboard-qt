#ifndef DISBOARD_MOVELISTMODEL_H
#define DISBOARD_MOVELISTMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QtQml/qqmlregistration.h>

#include "controller.h"

class VariationInfo {
    Q_GADGET
    QML_VALUE_TYPE(variationInfo)
    Q_PROPERTY(QUuid node MEMBER node CONSTANT)
    Q_PROPERTY(QString display MEMBER display CONSTANT)

public:
    VariationInfo() = default;
    VariationInfo(QUuid node, QString display)
        : node(node), display(std::move(display)) {}

private:
    QUuid node;
    QString display;
};

class MoveListModel : public QAbstractTableModel {
Q_OBJECT

    QML_ELEMENT
    Q_DISABLE_COPY(MoveListModel)

    Q_PROPERTY(Controller *controller READ controller WRITE setController NOTIFY controllerChanged REQUIRED)
    Q_PROPERTY(QUuid root READ root WRITE setRoot NOTIFY rootChanged)
public:
    enum ItemRoles {
        NodeRole = Qt::UserRole + 1,
        VariationsRole,
    };

    explicit MoveListModel(QObject *parent = nullptr);

    [[nodiscard]] int rowCount(const QModelIndex &parent) const override;
    [[nodiscard]] int columnCount(const QModelIndex &parent) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
    [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

    [[nodiscard]] Controller *controller() const;
    void setController(Controller *newValue);

    [[nodiscard]] QUuid root() const;
    void setRoot(QUuid newValue);

private:
    class p;
    std::shared_ptr<p> p;

    void reset(Controller* controller, QUuid root);
    void handleNodePushed(QUuid node);

signals:
    void controllerChanged();
    void rootChanged();
};


#endif //DISBOARD_MOVELISTMODEL_H
