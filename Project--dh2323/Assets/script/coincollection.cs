using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class coincollection : MonoBehaviour
{


    void OnTriggerEnter(Collider collider)
    {
        Destroy(gameObject);
        coinsystem.CoinsCollect += 1;

    }
    // Update is called once per frame
    void Update()
    {

    }
}
