#include "diff_init_destroy.h"

#include <assert.h>

Differentiator_t * DifferentiatorInit(void) {
    Differentiator_t * dif = (Differentiator_t *) calloc (1, sizeof(Differentiator_t));
    if (dif == NULL) {
        printf("ERROR: memory allocated failed %s:%d\n", __FILE__, __LINE__);
        return NULL;
    }

    dif->meaning = NOTHING;
    dif->value.number = 0;
    dif->parent = NULL;
    dif->right = NULL;
    dif->left = NULL;

    return dif;
}

void DifferentiatorDestroy(Differentiator_t ** dif) {
    if (dif == NULL || *dif == NULL) return;

    DifferentiatorDestroy(&(*dif)->left);
    DifferentiatorDestroy(&(*dif)->right);

    (*dif)->meaning = NOTHING;
    (*dif)->value.number = 0;
    (*dif)->left = NULL;
    (*dif)->right = NULL;
    (*dif)->parent = NULL;

    free(*dif);
    *dif = NULL;
    return;
}

/**
 * @brief Эта функция делает новую вернишу и сразу записывает в нее значение родителя
 * 
 * @param parent указатель на родителя который сразу записывается в новую вершину
 * 
 * @return указатель на новую вершину которое надо сразу записать в left или right родителя
 */
Differentiator_t * DifferentiatorNodeInit(Differentiator_t * parent) {
    if (parent == NULL) {
        printf("ERROR: differentiator parent NULL pointer %s:%d\n", __FILE__, __LINE__);
        return NULL;
    }

    Differentiator_t * dif = DifferentiatorInit();
    if (dif == NULL) {
        return NULL;
    }
    dif->parent = parent;

    return dif;
}

/**
 * @brief Эта функция создает динамическую копию всего поддерева и возвращает указатель на нее
 * 
 * @param dif указатель на поддерево копию которго надо сделать
 * @param copy_parent указатель на уже копию родителя
 * 
 * @return указатель на скопированное динамически поддерево
 */
Differentiator_t * DifferentiatorCopy(Differentiator_t * dif, Differentiator_t * copy_parent) {
    assert(dif);

    Differentiator_t * copy_dif = DifferentiatorInit();
    if (copy_dif == NULL) {
        return NULL;
    }

    copy_dif->meaning = dif->meaning;
    copy_dif->value = dif->value;
    copy_dif->parent = copy_parent;
    if (dif->left  != NULL) copy_dif->left  = DifferentiatorCopy(dif->left, copy_dif);
    if (dif->right != NULL) copy_dif->right = DifferentiatorCopy(dif->right, copy_dif);
    return copy_dif;
}
/**
 * @brief Эта функция создает вершину и устанавливает в ней ту или иную константу
 * 
 * @param parent указатель родителя листа в который надо поставить константу
 * @param value константа которую надо поставить в этот лист
 * 
 * @return созданную динамически вершину с константой внутри
 */
Differentiator_t * DifferentiatorNodeInitConst(Differentiator_t * parent, double value) {
    if (parent == NULL) {
        printf("ERROR: differentiator parent NULL pointer %s:%d\n", __FILE__, __LINE__);
        return NULL;
    }
    Differentiator_t * dif = DifferentiatorInit();
    if (dif == NULL) {
        return NULL;
    }
    dif->parent = parent;
    dif->meaning = VALUE;
    dif->value.number = value;
    return dif;
}

void EnterMeaning(Differentiator_t * dif, Meaning_t meaning) {
    dif->meaning = meaning;
}
void EnterValueNumber(Differentiator_t * dif, double value) {
    dif->value.number = value;
}
void EnterValueOperation(Differentiator_t * dif, Meaning_t operation) {
    if (!((START_BIN_OPERATIONS < operation && operation < END_BIN_OPERATIONS) || (START_UN_OPERATIONS < operation && operation < END_UN_OPERATIONS))) {
        printf("ERROR: entered illigal operation %s:%d\n", __FILE__, __LINE__);
        dif->value.operation = NOTHING;
        return;
    }
    dif->value.operation = operation;
}
void EnterValueVariable(Differentiator_t * dif, char variable) {
    if (!('a' <= variable && variable <= 'z')) {
        printf("ERROR: entered illigal variable %s:%d\n", __FILE__, __LINE__);
        dif->value.variable = '\0';
        return;
    }
    dif->value.variable = variable;
}