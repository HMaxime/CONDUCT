using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UIController : MonoBehaviour
{
    Slider stereoSlider;
    Slider volumeSlider;
    // Start is called before the first frame update
    void Start()
    {
        stereoSlider = gameObject.transform.GetChild(0).GetComponent<Slider>();
        volumeSlider = gameObject.transform.GetChild(1).GetComponent<Slider>();
        stereoSlider.value = 1;
    }

    public void setStereoSliderValue(float value)
    {
        this.stereoSlider.value = value;
    }

    public void setVolumeSliderValue(float value)
    {
        this.volumeSlider.value = value;
    }



}
