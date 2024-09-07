#include "../all"

typedef uint16_t eid_t;

private struct queue(eid_t) entities = {};
private eid_t max_entity = 0;

private function eid_t create_entity(void) {
    var const result = queue__front(eid_t, entities);
    if (NULL == result)
        return max_entity++;
    eid_t tmp = *result;
    free(queue__pop(eid_t, entities));
    return tmp;
}

private function void destroy_entity(eid_t entity) {
    queue__push(eid_t, entity, entities);
}

function int main(void) {
    eid_t _0, _1;

    _0 = create_entity();
    printn(_0);
   
    _1 = create_entity();
    printn(_1);
    
    destroy_entity(_0);
    destroy_entity(_1);

    _0 = create_entity();
    printn(_0);

    _1 = create_entity();
    printn(_1);

    destroy_entity(_1);
    destroy_entity(_0);

    _0 = create_entity();
    printn(_0);

    _1 = create_entity();
    printn(_1);

    queue__destroy(eid_t, NULL, entities);
}