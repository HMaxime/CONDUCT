using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class calculIndexPaume : MonoBehaviour
{
	public Transform tr1;
    public Transform tr2;
	 
    // Start is called before the first frame update
    void Start()
    {
        tr1 = this.gameObject.transform.GetChild(0).GetChild(5);
        tr2 = this.gameObject.transform.GetChild(0).GetChild(1).GetChild(0);
        print(tr1);
        print(tr2);

    }

    // Update is called once per frame
    void Update()
    {
        /*
        float distance = ComputeDistance(tr1, tr2);
        if (distance > 0.05) print("Main ouverte !!");
        else print("Main fermé !");
        */
    }

    float ComputeDistance(Transform tr1,Transform tr2)
    {
        return Mathf.Sqrt(Mathf.Pow((tr1.position.x - tr2.position.x), 2) + Mathf.Pow((tr1.position.y - tr2.position.y), 2) + Mathf.Pow((tr1.position.z - tr2.position.z), 2));
    }
}
