using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class coinsystem : MonoBehaviour {

    public static int CoinsCollect = 0;

    public void OnGUI()
    {
        GUI.Label(new Rect(10, 10, 300, 80), "Score:" + CoinsCollect);
    }
}
