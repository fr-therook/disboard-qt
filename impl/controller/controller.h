#ifndef DISBOARD_CONTROLLER_H
#define DISBOARD_CONTROLLER_H

#include <QObject>
#include <QUuid>
#include <QVariant>
#include <QPointF>
#include <QtQml/qqmlregistration.h>

#include "disboard.h"

class Controller : public QObject {
Q_OBJECT

    QML_ELEMENT
    Q_DISABLE_COPY(Controller)

    Q_PROPERTY(int pieceSize READ pieceSize WRITE setPieceSize NOTIFY pieceSizeChanged)

    Q_PROPERTY(QUuid root READ root NOTIFY rootChanged)
    Q_PROPERTY(QUuid curNode READ curNode WRITE setCurNode NOTIFY curNodeChanged)

    Q_PROPERTY(QVariant phantom READ phantom NOTIFY dragChanged)
    Q_PROPERTY(QPointF dragPos READ dragPos WRITE setDragPos NOTIFY dragPosChanged)
    Q_PROPERTY(disboard::Square dragSq READ dragSq NOTIFY dragPosChanged)

    Q_PROPERTY(QVariant highlightedSq READ highlightedSq NOTIFY highlightedSqChanged)
    Q_PROPERTY(QVariant lastSrcSq READ lastSrcSq NOTIFY curNodeChanged)
    Q_PROPERTY(QVariant lastDestSq READ lastDestSq NOTIFY curNodeChanged)

    Q_PROPERTY(QVector<disboard::Square> hintSq READ hintSq NOTIFY highlightedSqChanged)
    Q_PROPERTY(QVector<disboard::Square> captureSq READ captureSq NOTIFY highlightedSqChanged)

    Q_PROPERTY(QVariant promotionSq READ promotionSq NOTIFY promotionChanged)
    Q_PROPERTY(QVariant promotionPieces READ promotionPieces NOTIFY promotionChanged)

    Q_PROPERTY(QString pgn READ pgn NOTIFY treeChanged)

public:
    explicit Controller(QObject *parent = nullptr);

    Q_INVOKABLE
    void resyncBoard();

    Q_INVOKABLE
    void coordClicked(float x, float y);

    Q_INVOKABLE
    void coordDragStarted(
            float startX, float startY,
            float endX, float endY
    );

    Q_INVOKABLE
    void coordDragEnded(
            float startX, float startY,
            float endX, float endY
    );

    Q_INVOKABLE
    void promote(disboard::Piece piece);

    Q_INVOKABLE void prevMove();
    Q_INVOKABLE void nextMove();

    [[nodiscard]] int pieceSize() const;
    void setPieceSize(int newValue);

    [[nodiscard]] QUuid root() const;
    [[nodiscard]] QUuid curNode() const;
    void setCurNode(QUuid newValue);

    [[nodiscard]] QVariant phantom() const;
    [[nodiscard]] QPointF dragPos() const;
    void setDragPos(QPointF newValue);
    [[nodiscard]] disboard::Square dragSq() const;

    [[nodiscard]] QVariant highlightedSq() const;
    [[nodiscard]] QVariant lastSrcSq() const;
    [[nodiscard]] QVariant lastDestSq() const;

    [[nodiscard]] QVector<disboard::Square> hintSq() const;
    [[nodiscard]] QVector<disboard::Square> captureSq() const;

    [[nodiscard]] QVariant promotionSq() const;
    [[nodiscard]] QVariant promotionPieces() const;

    [[nodiscard]] QString pgn() const;

    [[nodiscard]] const disboard::Disboard& board() const;

private:
    class p;
    std::shared_ptr<p> p;

    QPointF mDragPos;

signals:
    void placePiece(disboard::Piece piece, disboard::Square square);
    void movePiece(disboard::Square from, disboard::Square to);
    void removePiece(disboard::Square square);
    void resetBoard(
        QVector<disboard::Square> squares,
        QVector<disboard::Piece> pieces
    );

    void pieceSizeChanged();

    void rootChanged();
    void curNodeChanged();
    void nodePushed(QUuid node);
    void treeChanged();

    void dragChanged();
    void dragPosChanged();

    void highlightedSqChanged();

    void promotionChanged();
};

#endif //DISBOARD_CONTROLLER_H
