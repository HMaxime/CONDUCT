using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class calculIndexPaume : MonoBehaviour
{
	public Transform tr;
	 
    // Start is called before the first frame update
    void Start()
    {
        tr = this.gameObject.transform;

		
    }

    // Update is called once per frame
    void Update()
    {
				print(tr.GetChild(0).gameObject.transform.GetChild(5).transform.position);

    }
}
