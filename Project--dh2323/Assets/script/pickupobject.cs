

using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class pickupobject : MonoBehaviour
{
    public Transform target;

    void Update()
    {

    }
    void OnMouseDown()
    {
        //GetComponent<Rigidbody>().useGravity=false;
        this.transform.position = target.position;
        this.transform.parent = GameObject.Find("FPSController").transform;
        this.transform.parent = GameObject.Find("FirstPersonCharacter").transform;
    }
    void OnMouseUp()
    {
        //GetComponent<Rigidbody>().useGravity = ture;
        this.transform.parent = GameObject.Find("FPSController").transform;
        this.transform.parent = null; // unperent the GameObject From The Target
    }

}﻿
 
/*
public class pickupobject : MonoBehaviour
{
    public Transform player;
    public Transform playerCam;
    public float throwForce = 10;
    bool hasPlayer = false;
    bool beingCarried = false;
    public AudioClip[] soundToPlay;
    private AudioSource audio;
    public int dmg;
    private bool touched = false;

    void Start()
    {
        audio = GetComponent<AudioSource>();
    }

    void Update()
    {
        float dist = Vector3.Distance(gameObject.transform.position, player.position);
        if (dist <= 2.5f)
        {
            hasPlayer = true;
        }
        else
        {
            hasPlayer = false;
        }
        if (hasPlayer && Input.GetButtonDown("Use"))
        {
            GetComponent<Rigidbody>().isKinematic = true;
            transform.parent = playerCam;
            beingCarried = true;
        }
        if (beingCarried)
        {
            if (touched)
            {
                GetComponent<Rigidbody>().isKinematic = false;
                transform.parent = null;
                beingCarried = false;
                touched = false;
            }
            if (Input.GetMouseButtonDown(0))
            {
                GetComponent<Rigidbody>().isKinematic = false;
                transform.parent = null;
                beingCarried = false;
                GetComponent<Rigidbody>().AddForce(playerCam.forward * throwForce);
                RandomAudio();
            }
            else if (Input.GetMouseButtonDown(1))
            {
                GetComponent<Rigidbody>().isKinematic = false;
                transform.parent = null;
                beingCarried = false;
            }
        }
    }
    void RandomAudio()
    {
        if (audio.isPlaying)
        {
            return;
        }
        audio.clip = soundToPlay[Random.Range(0, soundToPlay.Length)];
        audio.Play();

    }
    void OnTriggerEnter()
    {
        if (beingCarried)
        {
            touched = true;
        }
    }
}
*/
/*
public class pickupobject : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
*/
/*
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Pickupable : MonoBehaviour {
    GameObject mainCamera;
    bool carrying;
    GameObject carriedObject;
	// Use this for initialization
	void Start () {
        mainCamera = GameObject.FindWithTag("MainCamera");
	}
	// Update is called once per frame
	void Update () {
		if(carrying)
        {
            carry(carriedObject);
        }
        else { pickup(); }
	}
    void carry(GameObject o)
    {

    }
    void pickup()
    {
        if(Input.GetKeyDown(KeyCode.R))
        {
            int x = Screen.width / 2;
            int y = Screen.height / 2;

            Ray ray = mainCamera.camera.ScreenPointToRay(new Vector3(x, y));
            
        }
    }
}
*/
/*var target: Transform;

function Update(){

}

function OnMouseDown (){
    this.transform.position= target.postion;
    this.transform.parent= GameObject.Find("FPSController").transform;
    this.transform.parent=GameObject.Find("FirstPersonCharacter").transform;

}

function OnMouseUp(){
    this.transform.parent=GameObject.Find("FPSController").transform;
    this.transform.parent=null;
}
*/